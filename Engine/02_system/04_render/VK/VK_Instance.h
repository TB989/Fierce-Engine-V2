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

struct EngineSettings;

class VK_Instance{
public:
	VK_Instance(EngineSettings* settings);
	~VK_Instance();

public:
	void addRequiredExtension(const char* extension);
	void addDesiredExtension(const char* extension);
	void addRequiredValidationLayer(const char* layer);
	void addDesiredValidationLayer(const char* layer);

	void create();
	VkInstance getId();

	void linkDebug(VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo);

	void printSupportedExtensions();
	void printEnabledExtensions();

	void printSupportedValidationLayers();
	void printEnabledValidationLayers();

private:
	void getSupportedExtensions();
	bool isExtensionSupported(const char* extensionName);
	void checkExtensionSupport();

	void getSupportedValidationLayers();
	bool isValidationlayerSupported(const char* layerName);
	void checkValidationLayerSupport();

private:
	VkInstanceCreateInfo createInfo{};
	VkInstance instance;

private:
	uint32_t API_VERSION;
	std::string APP_NAME = "FIERCE-APP";
	uint32_t APP_VERSION= VK_MAKE_VERSION(1, 0, 0);
	std::string ENGINE_NAME = "FIERCE-ENGINE";
	uint32_t ENGINE_VERSION = VK_MAKE_VERSION(1, 0, 0);

	std::vector<VkExtensionProperties> supportedExtensions;
	std::vector<const char*> requiredExtensions;
	std::vector<const char*> desiredExtensions;
	std::vector<const char*> enabledExtensions;

	std::vector<VkLayerProperties> supportedValidationLayers;
	std::vector<const char*> requiredValidationLayers;
	std::vector<const char*> desiredValidationLayers;
	std::vector<const char*> enabledValidationLayers;
};