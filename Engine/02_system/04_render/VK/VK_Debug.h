#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/

/* SystemIncludes*/
#include "vulkan/vulkan.h"

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/

class VK_Debug{
public:
	VK_Debug();
	~VK_Debug();

	VkDebugUtilsMessengerCreateInfoEXT getCreateInfo();
	void create(VkInstance instance);
	

private:
	PFN_vkCreateDebugUtilsMessengerEXT loadCreateFunctionPointer(VkInstance instance);
	PFN_vkDestroyDebugUtilsMessengerEXT loadDestroyFunctionPointer(VkInstance instance);

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

private:
	VkInstance m_instance;
	VkDebugUtilsMessengerCreateInfoEXT createInfo{};
	VkDebugUtilsMessengerEXT debugMessenger;

	PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXT;
	PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT;
};