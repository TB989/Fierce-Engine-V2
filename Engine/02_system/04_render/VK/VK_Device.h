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
	VK_Device(VkInstance instance, VkSurfaceKHR surface);
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

	VkDevice getDevice() { return device; }

	VkSurfaceFormatKHR getSurfaceFormat(){ return surfaceFormat; }
	VkPresentModeKHR getPresentMode() { return presentMode; }
	VkExtent2D getExtent() {return extent;}
	uint32_t getNumberOfImages() { return imageCount; }
	VkSurfaceTransformFlagBitsKHR getSurfaceTransform(){ return surfaceTransform; }

private:
	void choosePhysicalDevice();
	bool isDeviceSuitable(VkPhysicalDevice device);
	VkBool32 supportsPresent(VkPhysicalDevice physicalDevice,int queueIndex);
	bool checkSwapchainSupport(VkPhysicalDevice physicalDevice);
	bool chooseSwapchainSettings(VkSurfaceCapabilitiesKHR surfaceCapabilities, std::vector<VkSurfaceFormatKHR> formats, std::vector<VkPresentModeKHR> presentModes);
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
	VkSurfaceKHR m_surface;
	VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
	int queueFamilyIndex=-1;
	VkDevice device;
	VkQueue graphicsQueue;

	VkSurfaceFormatKHR surfaceFormat;
	VkPresentModeKHR presentMode;
	VkExtent2D extent;
	uint32_t imageCount;
	VkSurfaceTransformFlagBitsKHR surfaceTransform;

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