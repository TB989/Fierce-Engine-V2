#include "VK_Debug.h"

#include "01_core/errorHandling/Exceptions.h"
#include "02_system/01_logging/Logger.h"

VK_Debug::VK_Debug(){
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = debugCallback;
	createInfo.pUserData = nullptr;
}

VK_Debug::~VK_Debug(){
	vkDestroyDebugUtilsMessengerEXT(m_instance, debugMessenger, nullptr);
}

VkDebugUtilsMessengerCreateInfoEXT VK_Debug::getCreateInfo(){
	return createInfo;
}

void VK_Debug::create(VkInstance instance){
	m_instance = instance;

	vkCreateDebugUtilsMessengerEXT = loadCreateFunctionPointer(instance);
	vkDestroyDebugUtilsMessengerEXT = loadDestroyFunctionPointer(instance);

	CHECK_VK(vkCreateDebugUtilsMessengerEXT(m_instance, &createInfo, nullptr, &debugMessenger),"Failed to create debug messenger.");
}

PFN_vkCreateDebugUtilsMessengerEXT VK_Debug::loadCreateFunctionPointer(VkInstance instance){
	PFN_vkCreateDebugUtilsMessengerEXT func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

	if (func == nullptr) {
		CHECK_VK(VK_ERROR_EXTENSION_NOT_PRESENT, "Failed to load function pointer for vkCreateDebugUtilsMessengerEXT.");
		return nullptr;
	}
	return func;
}

PFN_vkDestroyDebugUtilsMessengerEXT VK_Debug::loadDestroyFunctionPointer(VkInstance instance){
	PFN_vkDestroyDebugUtilsMessengerEXT func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");

	if (func == nullptr) {
		CHECK_VK(VK_ERROR_EXTENSION_NOT_PRESENT, "Failed to load function pointer for vkDestroyDebugUtilsMessengerEXT.");
		return nullptr;
	}
	return func;
}

VKAPI_ATTR VkBool32 VKAPI_CALL VK_Debug::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,	VkDebugUtilsMessageTypeFlagsEXT messageType,const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,void* pUserData) {
	Loggers::VK->error("%s",pCallbackData->pMessage);
	return VK_FALSE;
}