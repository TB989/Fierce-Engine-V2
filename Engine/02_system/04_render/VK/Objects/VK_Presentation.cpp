#include "VK_Presentation.h"

#include "01_core/Core.h"
#include "01_core/errorHandling/Exceptions.h"
#include "02_system/02_event/EventSystem.h"
#include "02_system/02_event/Event.h"


VK_Presentation::VK_Presentation(Core* core, VkInstance instance){
	m_instance = instance;

	core->eventSystem->addListener(this, &VK_Presentation::onHandleReceived);
	core->eventSystem->postEvent(new WindowRequestHandleEvent(false));
	if (windowHandle == nullptr) {
		CHECK_VK(VK_ERROR_INITIALIZATION_FAILED, "Failed to get valid window handles for vulkan surface.");
	}
}

VK_Presentation::~VK_Presentation(){
	vkDestroySurfaceKHR(m_instance,surface,nullptr);
}

void VK_Presentation::createSurface(){
	VkWin32SurfaceCreateInfoKHR createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.hwnd = windowHandle;
	createInfo.hinstance = GetModuleHandle(nullptr);

	CHECK_VK(vkCreateWin32SurfaceKHR(m_instance, &createInfo, nullptr, &surface),"Failed to create vulkan surface.");
}

void VK_Presentation::createSwapchain(VK_Device* device) {
	m_device = device->getDevice();

	VkSwapchainCreateInfoKHR createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.surface = surface;
	createInfo.minImageCount = device->getNumberOfImages();
	createInfo.imageFormat = device->getSurfaceFormat().format;
	createInfo.imageColorSpace = device->getSurfaceFormat().colorSpace;
	createInfo.imageExtent = device->getExtent();
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	createInfo.queueFamilyIndexCount = 0;
	createInfo.pQueueFamilyIndices = nullptr;
	createInfo.preTransform = device->getSurfaceTransform();
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode = device->getPresentMode();
	createInfo.clipped = VK_TRUE;
	createInfo.oldSwapchain = VK_NULL_HANDLE;

	CHECK_VK(vkCreateSwapchainKHR(m_device, &createInfo, nullptr, &swapChain), "Failed to create swapchain.");

	uint32_t imageCount;
	CHECK_VK(vkGetSwapchainImagesKHR(m_device, swapChain, &imageCount, nullptr), "Failed to get swapchain images.");
	swapChainImages.resize(imageCount);
	CHECK_VK(vkGetSwapchainImagesKHR(m_device, swapChain, &imageCount, swapChainImages.data()), "Failed to get swapchain images.");

	swapChainImageViews.resize(swapChainImages.size());
	for (size_t i = 0; i < swapChainImages.size(); i++) {
		VkImageViewCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.pNext = nullptr;
		createInfo.flags = 0;
		createInfo.image = swapChainImages[i];
		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = device->getSurfaceFormat().format;
		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		createInfo.subresourceRange.baseMipLevel = 0;
		createInfo.subresourceRange.levelCount = 1;
		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.layerCount = 1;

		CHECK_VK(vkCreateImageView(m_device, &createInfo, nullptr, &swapChainImageViews[i]),"Failed to create image view for swapchain.");
	}
}

void VK_Presentation::destroySwapchain(){
	for (auto imageView : swapChainImageViews) {
		vkDestroyImageView(m_device, imageView, nullptr);
	}
	vkDestroySwapchainKHR(m_device, swapChain, nullptr);
}

void VK_Presentation::onHandleReceived(WindowSendHandleEvent* evt) {
	windowHandle = evt->m_handle;
}