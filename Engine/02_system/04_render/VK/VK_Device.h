#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "99_utils/FierceStrings.h"

/* SystemIncludes*/
#include "vulkan/vulkan.h"
#include <vector>

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/

class VK_Device{
public:
	VK_Device(VkInstance instance);
	~VK_Device();

public:
	void addRequiredExtension(const char* extension);
	void addDesiredExtension(const char* extension);
	void addRequiredValidationLayer(const char* layer);
	void addDesiredValidationLayer(const char* layer);

	void create();

	void printSupportedExtensions();
	void printEnabledExtensions();

	void printSupportedValidationLayers();
	void printEnabledValidationLayers();

private:
	void choosePhysicalDevice();
	bool isDeviceSuitable(VkPhysicalDevice device);
	void createLogicalDevice();

private:
	void getSupportedExtensions();
	bool isExtensionSupported(const char* extensionName);
	void checkExtensionSupport();

	void getSupportedValidationLayers();
	bool isValidationlayerSupported(const char* layerName);
	void checkValidationLayerSupport();

private:
	VkInstance m_instance;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	int queueFamilyIndex;
	VkDevice device;
	VkQueue graphicsQueue;

private:
	std::vector<VkExtensionProperties> supportedExtensions;
	std::vector<const char*> requiredExtensions;
	std::vector<const char*> desiredExtensions;
	std::vector<const char*> enabledExtensions;

	std::vector<VkLayerProperties> supportedValidationLayers;
	std::vector<const char*> requiredValidationLayers;
	std::vector<const char*> desiredValidationLayers;
	std::vector<const char*> enabledValidationLayers;
};