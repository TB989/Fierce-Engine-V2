#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "02_system/04_render/VK/VK_Device.h"

/* SystemIncludes*/
#include "vulkan/vulkan.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <vector>

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/
class Core;
struct WindowSendHandleEvent;

class VK_Presentation{

public:
	VK_Presentation(Core* core, VkInstance instance);
	~VK_Presentation();

	void createSurface();
	void createSwapchain(VK_Device* device);

	void destroySwapchain();

	VkSurfaceKHR getSurface() { return surface; }
	int getNumImages() { return swapChainImageViews.size(); }
	VkImageView getImageView(int index) { return swapChainImageViews[index]; }

	VkSwapchainKHR getSwapchain() { return swapChain; }

private:
	VkInstance m_instance;
	VkDevice m_device;
	HWND windowHandle = nullptr;
	VkSurfaceKHR surface;
	VkSwapchainKHR swapChain;

	std::vector<VkImage> swapChainImages;
	std::vector<VkImageView> swapChainImageViews;

private:
	void onHandleReceived(WindowSendHandleEvent* evt);
};