#include "VK_Device.h"

#include "01_core/errorHandling/Exceptions.h"
#include "02_system/01_logging/Logger.h"

VK_Device::VK_Device(VkInstance instance){
    m_instance = instance;
    choosePhysicalDevice();
	getSupportedExtensions();
	getSupportedValidationLayers();
}

VK_Device::~VK_Device() {
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
            physicalDevice = device;
            break;
        }
    }

    if (physicalDevice == VK_NULL_HANDLE) {
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

    int i = 0;
    for (VkQueueFamilyProperties queueFamily : queueFamilies) {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            queueFamilyIndex = i;
            return true;
        }
        i++;
    }
    return false;
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

    CHECK_VK(vkCreateDevice(physicalDevice, &createInfo, nullptr, &device), "Failed to create logical device.");
}

void VK_Device::getSupportedExtensions() {
    uint32_t extensionCount = 0;
    CHECK_VK(vkEnumerateDeviceExtensionProperties(physicalDevice,nullptr, &extensionCount, nullptr), "Failed to enumerate device extensions.");
    supportedExtensions.resize(extensionCount);
    CHECK_VK(vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, supportedExtensions.data()), "Failed to enumerate device extensions.");
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
    CHECK_VK(vkEnumerateDeviceLayerProperties(physicalDevice, &layerCount, nullptr), "Failed to enumerate device validation layers.");
    supportedValidationLayers.resize(layerCount);
    CHECK_VK(vkEnumerateDeviceLayerProperties(physicalDevice, &layerCount, supportedValidationLayers.data()), "Failed to enumerate device validation layers.");
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