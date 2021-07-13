#include "VK_Device.h"

#include "01_core/errorHandling/Exceptions.h"
#include "02_system/01_logging/Logger.h"

#include "02_system/04_render/VK/VK_Renderpass.h"
#include "02_system/04_render/VK/VK_Framebuffers.h"
#include "02_system/04_render/VK/VK_Pipeline.h"

VK_Device::VK_Device(VkInstance instance, VkSurfaceKHR surface){
    m_instance = instance;
    m_surface = surface;

    choosePhysicalDevice();
	getSupportedExtensions();
	getSupportedValidationLayers();
}

VK_Device::~VK_Device() {
    vkFreeCommandBuffers(device, commandPool, commandBuffers.size(), commandBuffers.data());
    vkDestroyCommandPool(device, commandPool, nullptr);
    vkDestroyDevice(device, nullptr);
}

void VK_Device::addRequiredExtension(const char* extension) {
    requiredExtensions.push_back(extension);
}

void VK_Device::addDesiredExtension(const char* extension) {
    desiredExtensions.push_back(extension);
}

void VK_Device::addRequiredValidationLayer(const char* layer) {
    requiredValidationLayers.push_back(layer);
}

void VK_Device::addDesiredValidationLayer(const char* layer) {
    desiredValidationLayers.push_back(layer);
}

void VK_Device::create() {
    checkExtensionSupport();
    checkValidationLayerSupport();

    createLogicalDevice();

    vkGetDeviceQueue(device, queueFamilyIndex, 0, &graphicsQueue);
}

void VK_Device::printSupportedExtensions() {
    Loggers::VK->info("### Number of available device extensions: %i ###", supportedExtensions.size());
    for (const auto& extension : supportedExtensions) {
        Loggers::VK->info("\t%s", extension.extensionName);
    }
}

void VK_Device::printEnabledExtensions() {
    Loggers::VK->info("### Number of enabled device extensions: %i ###", enabledExtensions.size());
    for (const auto& extension : enabledExtensions) {
        Loggers::VK->info("\t%s", extension);
    }
}

void VK_Device::printSupportedValidationLayers() {
    Loggers::VK->info("### Number of available device validation layers: %i ###", supportedValidationLayers.size());
    for (const auto& layer : supportedValidationLayers) {
        Loggers::VK->info("\t%s", layer.layerName);
    }
}

void VK_Device::printEnabledValidationLayers() {
    Loggers::VK->info("### Number of enabled device validation layers: %i ###", enabledValidationLayers.size());
    for (const auto& layer : enabledValidationLayers) {
        Loggers::VK->info("\t%s", layer);
    }
}

void VK_Device::createCommandPool(){
    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.pNext = nullptr;
    poolInfo.flags = 0;
    poolInfo.queueFamilyIndex = queueFamilyIndex;

    CHECK_VK(vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool),"Failed to create command pool.");
}

void VK_Device::createCommandBuffers(int numBuffers){
    commandBuffers.resize(numBuffers);

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.pNext = nullptr;
    allocInfo.commandPool = commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = (uint32_t)numBuffers;

    CHECK_VK(vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data()),"Failed to allocate command buffers.");
}

void VK_Device::recordCommandBuffers(VK_Renderpass* renderpass, VK_Framebuffers* framebuffers, VK_Pipeline* pipeline){
    for (size_t i = 0; i < commandBuffers.size(); i++) {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.pNext = nullptr;
        beginInfo.flags = 0; // Optional
        beginInfo.pInheritanceInfo = nullptr; // Optional
        CHECK_VK(vkBeginCommandBuffer(commandBuffers[i], &beginInfo),"Failed to begin recording command buffer.");

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.pNext = nullptr;
        renderPassInfo.renderPass = renderpass->getRenderpass();
        renderPassInfo.framebuffer = framebuffers->getFramebuffer(i);
        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = extent;
        VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;
        vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->getPipeline());

        vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

        vkCmdEndRenderPass(commandBuffers[i]);

        CHECK_VK(vkEndCommandBuffer(commandBuffers[i]),"Failed to end recording command buffer.");
    }
}

void VK_Device::choosePhysicalDevice(){
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);
    if (deviceCount == 0) {
        CHECK_VK(VK_ERROR_INCOMPATIBLE_DRIVER,"No graphics card with vulkan support found.");
    }
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(m_instance, &deviceCount, devices.data());

    for (VkPhysicalDevice device : devices) {
        if (isDeviceSuitable(device)) {
            m_physicalDevice = device;
            break;
        }
    }

    if (m_physicalDevice == VK_NULL_HANDLE) {
        CHECK_VK(VK_ERROR_INCOMPATIBLE_DRIVER, "No graphics card supports all features needed to run this engine.");
    }
}

bool VK_Device::isDeviceSuitable(VkPhysicalDevice device){
    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;
    VkPhysicalDeviceMemoryProperties deviceMemoryProperties;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
    vkGetPhysicalDeviceMemoryProperties(device,&deviceMemoryProperties);

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    VkSurfaceCapabilitiesKHR surfaceCapabilities;
    CHECK_VK(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, m_surface, &surfaceCapabilities),"Failed to get surface capabilities.");
    uint32_t formatCount;
    CHECK_VK(vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_surface, &formatCount, nullptr),"Failed to get surface formats.");
    std::vector<VkSurfaceFormatKHR> formats(formatCount);
    CHECK_VK(vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_surface, &formatCount, formats.data()), "Failed to get surface formats.");
    uint32_t presentModeCount;
    CHECK_VK(vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_surface, &presentModeCount, nullptr),"Failed to get present modes.");
    std::vector<VkPresentModeKHR> presentModes(presentModeCount);
    CHECK_VK(vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_surface, &presentModeCount, presentModes.data()), "Failed to get present modes.");

    //Check queues
    int i = 0;
    for (VkQueueFamilyProperties queueFamily : queueFamilies) {
        if ((queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)&&supportsPresent(device,i)) {
            queueFamilyIndex = i;
            break;
        }
        i++;
    }
    if (queueFamilyIndex==-1) {
        return false;
    }

    //Check swapchain
    //checkSwapchainSupport(device)

    if (!chooseSwapchainSettings(surfaceCapabilities, formats, presentModes)) {
        return false;
    }

    return true;
}

VkBool32 VK_Device::supportsPresent(VkPhysicalDevice physicalDevice,int queueIndex){
    VkBool32 presentSupport = false;
    CHECK_VK(vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, queueIndex, m_surface, &presentSupport), "Failed to check presentation support.");
    return presentSupport;
}

bool VK_Device::checkSwapchainSupport(VkPhysicalDevice physicalDevice){
    for (const auto& extension : enabledExtensions) {
        if (strcmp(extension, VK_KHR_SWAPCHAIN_EXTENSION_NAME) == 0) {
            return true;
        }
    }
    return false;
}

bool VK_Device::chooseSwapchainSettings(VkSurfaceCapabilitiesKHR capabilities,std::vector<VkSurfaceFormatKHR> formats, std::vector<VkPresentModeKHR> presentModes){
    //Check surface format
    for (const auto& availableFormat : formats) {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            surfaceFormat = availableFormat;
        }
    }

    //Check present mode
    for (const auto& availablePresentMode : presentModes) {
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
            presentMode=availablePresentMode;
        }
    }

    //Check swapchain extent
    extent = capabilities.currentExtent;
    extent.width = max(extent.width, capabilities.minImageExtent.width);
    extent.width = min(extent.width, capabilities.maxImageExtent.width);
    extent.height = max(extent.height, capabilities.minImageExtent.height);
    extent.height = min(extent.height, capabilities.maxImageExtent.height);

    //Check number of images
    imageCount = capabilities.minImageCount + 1;
    if (capabilities.maxImageCount > 0 && imageCount > capabilities.maxImageCount) {
        imageCount = capabilities.maxImageCount;
    }

    surfaceTransform = capabilities.currentTransform;

    return true;
}

void VK_Device::createLogicalDevice(){
    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
    queueCreateInfo.queueCount = 1;
    float queuePriority = 1.0f;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    VkPhysicalDeviceFeatures deviceFeatures{};
    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pNext = nullptr;
    createInfo.flags = 0;
    createInfo.queueCreateInfoCount = 1;
    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.pEnabledFeatures = &deviceFeatures;
    if (enabledExtensions.empty()) {
        createInfo.enabledExtensionCount = 0;
        createInfo.ppEnabledExtensionNames = nullptr;
    }
    else {
        createInfo.enabledExtensionCount = static_cast<uint32_t>(enabledExtensions.size());
        createInfo.ppEnabledExtensionNames = enabledExtensions.data();
    }
    if (enabledValidationLayers.empty()) {
        createInfo.enabledLayerCount = 0;
        createInfo.ppEnabledLayerNames = nullptr;
    }
    else {
        createInfo.enabledLayerCount = static_cast<uint32_t>(enabledValidationLayers.size());
        createInfo.ppEnabledLayerNames = enabledValidationLayers.data();
    }

    CHECK_VK(vkCreateDevice(m_physicalDevice, &createInfo, nullptr, &device), "Failed to create logical device.");
}

void VK_Device::getSupportedExtensions() {
    uint32_t extensionCount = 0;
    CHECK_VK(vkEnumerateDeviceExtensionProperties(m_physicalDevice,nullptr, &extensionCount, nullptr), "Failed to enumerate device extensions.");
    supportedExtensions.resize(extensionCount);
    CHECK_VK(vkEnumerateDeviceExtensionProperties(m_physicalDevice, nullptr, &extensionCount, supportedExtensions.data()), "Failed to enumerate device extensions.");
}

bool VK_Device::isExtensionSupported(const char* extensionName) {
    for (const auto& extension : supportedExtensions) {
        if (strcmp(extension.extensionName, extensionName) == 0) {
            return true;
        }
    }
    return false;
}

void VK_Device::checkExtensionSupport() {
    for (const auto& extension : requiredExtensions) {
        if (isExtensionSupported(extension)) {
            enabledExtensions.push_back(extension);
        }
        else {
            Loggers::VK->error("Required device extension %s is not supported.", extension);
            CHECK_VK(VK_ERROR_EXTENSION_NOT_PRESENT, "Required device extensions are not supported.");
        }
    }

    for (const auto& extension : desiredExtensions) {
        if (isExtensionSupported(extension)) {
            enabledExtensions.push_back(extension);
        }
        else {
            Loggers::VK->warn("Desired device extension %s is not supported.", extension);
        }
    }
}

void VK_Device::getSupportedValidationLayers() {
    uint32_t layerCount = 0;
    CHECK_VK(vkEnumerateDeviceLayerProperties(m_physicalDevice, &layerCount, nullptr), "Failed to enumerate device validation layers.");
    supportedValidationLayers.resize(layerCount);
    CHECK_VK(vkEnumerateDeviceLayerProperties(m_physicalDevice, &layerCount, supportedValidationLayers.data()), "Failed to enumerate device validation layers.");
}

bool VK_Device::isValidationlayerSupported(const char* layerName) {
    for (const auto& layer : supportedValidationLayers) {
        if (strcmp(layer.layerName, layerName) == 0) {
            return true;
        }
    }
    return false;
}

void VK_Device::checkValidationLayerSupport() {
    for (const auto& layer : requiredValidationLayers) {
        if (isValidationlayerSupported(layer)) {
            enabledValidationLayers.push_back(layer);
        }
        else {
            Loggers::VK->error("Required device validation layer %s is not supported.", layer);
            CHECK_VK(VK_ERROR_LAYER_NOT_PRESENT, "Required device validation layers are not supported.");
        }
    }

    for (const auto& layer : desiredValidationLayers) {
        if (isValidationlayerSupported(layer)) {
            enabledValidationLayers.push_back(layer);
        }
        else {
            Loggers::VK->warn("Desired device validation layer %s is not supported.", layer);
        }
    }
}