#include "VK_Instance.h"

#include "01_core/EngineSettings.h"
#include "01_core/errorHandling/Exceptions.h"
#include "02_system/01_logging/Logger.h"

#include <algorithm>

VK_Instance::VK_Instance(EngineSettings* settings) {
    API_VERSION= VK_MAKE_VERSION(settings->apiVersionMajor, settings->apiVersionMinor, 0);
    getSupportedExtensions();
    getSupportedValidationLayers();
}

VK_Instance::~VK_Instance() {
    if (isDebugSupported) {
        vkDestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
    }
    vkDestroyInstance(instance, nullptr);
}

void VK_Instance::addRequiredExtension(const char* extension){
    requiredExtensions.push_back(extension);
}

void VK_Instance::addDesiredExtension(const char* extension){
    desiredExtensions.push_back(extension);
}

void VK_Instance::addRequiredValidationLayer(const char* layer) {
    requiredValidationLayers.push_back(layer);
}

void VK_Instance::addDesiredValidationLayer(const char* layer){
    desiredValidationLayers.push_back(layer);
}

void VK_Instance::create(){
    checkExtensionSupport();
    checkValidationLayerSupport();
    isDebugSupported = checkDebugSupport();

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pNext = nullptr;
    appInfo.pApplicationName = APP_NAME.c_str();
    appInfo.applicationVersion = APP_VERSION;
    appInfo.pEngineName = ENGINE_NAME.c_str();
    appInfo.engineVersion = ENGINE_VERSION;
    appInfo.apiVersion = API_VERSION;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pNext = nullptr;
    createInfo.flags = 0;
    createInfo.pApplicationInfo = &appInfo;
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

    if (isDebugSupported) {
        Loggers::VK->info("Debug messenger is active.");

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
        debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        debugCreateInfo.pNext = nullptr;
        debugCreateInfo.flags = 0;
        debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        debugCreateInfo.pfnUserCallback = debugCallback;
        debugCreateInfo.pUserData = nullptr;

        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
        CHECK_VK(vkCreateInstance(&createInfo, nullptr, &instance), "Failed to create instance.");

        vkCreateDebugUtilsMessengerEXT = loadCreateFunctionPointer(instance);
        vkDestroyDebugUtilsMessengerEXT = loadDestroyFunctionPointer(instance);

        CHECK_VK(vkCreateDebugUtilsMessengerEXT(instance, &debugCreateInfo, nullptr, &debugMessenger), "Failed to create debug messenger.");
    }
    else {
        Loggers::VK->info("Debug messenger is not active.");
        CHECK_VK(vkCreateInstance(&createInfo, nullptr, &instance), "Failed to create instance.");
    }
}

VkInstance VK_Instance::getId(){
    return instance;
}

void VK_Instance::printSupportedExtensions(){
    Loggers::VK->info("### Number of available instance extensions: %i ###", supportedExtensions.size());
    for (const auto& extension : supportedExtensions) {
        Loggers::VK->info("\t%s", extension.extensionName);
    }
}

void VK_Instance::printEnabledExtensions(){
    Loggers::VK->info("### Number of enabled instance extensions: %i ###", enabledExtensions.size());
    for (const auto& extension : enabledExtensions) {
        Loggers::VK->info("\t%s", extension);
    }
}

void VK_Instance::printSupportedValidationLayers(){
    Loggers::VK->info("### Number of available instance validation layers: %i ###", supportedValidationLayers.size());
    for (const auto& layer : supportedValidationLayers) {
        Loggers::VK->info("\t%s", layer.layerName);
    }
}

void VK_Instance::printEnabledValidationLayers(){
    Loggers::VK->info("### Number of enabled instance validation layers: %i ###", enabledValidationLayers.size());
    for (const auto& layer : enabledValidationLayers) {
        Loggers::VK->info("\t%s", layer);
    }
}

void VK_Instance::getSupportedExtensions(){
    uint32_t extensionCount = 0;
    CHECK_VK(vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr), "Failed to enumerate instance extensions.");
    supportedExtensions.resize(extensionCount);
    CHECK_VK(vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, supportedExtensions.data()), "Failed to enumerate instance extensions.");
}

bool VK_Instance::isExtensionSupported(const char* extensionName){
    for (const auto& extension : supportedExtensions) {
        if (strcmp(extension.extensionName, extensionName)==0) {
            return true;
        }
    }
    return false;
}

void VK_Instance::checkExtensionSupport(){
    for (const auto& extension : requiredExtensions) {
        if (isExtensionSupported(extension)) {
            enabledExtensions.push_back(extension);
        }
        else {
            Loggers::VK->error("Required instance extension %s is not supported.", extension);
            CHECK_VK(VK_ERROR_EXTENSION_NOT_PRESENT, "Required instance extensions are not supported.");
        }
    }

    for (const auto& extension : desiredExtensions) {
        if (isExtensionSupported(extension)) {
            enabledExtensions.push_back(extension);
        }
        else {
            Loggers::VK->warn("Desired instance extension %s is not supported.", extension);
        }
    }
}

bool VK_Instance::checkDebugSupport(){
    for (const auto& extension : enabledExtensions) {
        if (strcmp(extension, VK_EXT_DEBUG_UTILS_EXTENSION_NAME) == 0) {
            return true;
        }
    }
    return false;
}

void VK_Instance::getSupportedValidationLayers(){
    uint32_t layerCount = 0;
    CHECK_VK(vkEnumerateInstanceLayerProperties(&layerCount, nullptr), "Failed to enumerate instance validation layers.");
    supportedValidationLayers.resize(layerCount);
    CHECK_VK(vkEnumerateInstanceLayerProperties(&layerCount, supportedValidationLayers.data()), "Failed to enumerate instance validation layers.");
}

bool VK_Instance::isValidationlayerSupported(const char* layerName){
    for (const auto& layer : supportedValidationLayers) {
        if (strcmp(layer.layerName, layerName) == 0) {
            return true;
        }
    }
    return false;
}

void VK_Instance::checkValidationLayerSupport(){
    for (const auto& layer : requiredValidationLayers) {
        if (isValidationlayerSupported(layer)) {
            enabledValidationLayers.push_back(layer);
        }
        else {
            Loggers::VK->error("Required instance validation layer %s is not supported.", layer);
            CHECK_VK(VK_ERROR_LAYER_NOT_PRESENT, "Required instance validation layers are not supported.");
        }
    }

    for (const auto& layer : desiredValidationLayers) {
        if (isValidationlayerSupported(layer)) {
            enabledValidationLayers.push_back(layer);
        }
        else {
            Loggers::VK->warn("Desired instance validation layer %s is not supported.", layer);
        }
    }
}

PFN_vkCreateDebugUtilsMessengerEXT VK_Instance::loadCreateFunctionPointer(VkInstance instance) {
    PFN_vkCreateDebugUtilsMessengerEXT func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

    if (func == nullptr) {
        CHECK_VK(VK_ERROR_EXTENSION_NOT_PRESENT, "Failed to load function pointer for vkCreateDebugUtilsMessengerEXT.");
        return nullptr;
    }
    return func;
}

PFN_vkDestroyDebugUtilsMessengerEXT VK_Instance::loadDestroyFunctionPointer(VkInstance instance) {
    PFN_vkDestroyDebugUtilsMessengerEXT func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");

    if (func == nullptr) {
        CHECK_VK(VK_ERROR_EXTENSION_NOT_PRESENT, "Failed to load function pointer for vkDestroyDebugUtilsMessengerEXT.");
        return nullptr;
    }
    return func;
}

VKAPI_ATTR VkBool32 VKAPI_CALL VK_Instance::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
    Loggers::VK->error("%s", pCallbackData->pMessage);
    return VK_FALSE;
}