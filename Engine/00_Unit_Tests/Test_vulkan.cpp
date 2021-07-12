#include "UnitTests.h"

#include "02_system/02_event/EventSystem.h"

#include "02_system/04_render/VK/VK_Instance.h"
#include "02_system/04_render/VK/VK_Device.h"
#include "02_system/04_render/VK/VK_Presentation.h"
#include "02_system/04_render/VK/VK_Renderpass.h"
#include "02_system/04_render/VK/VK_Pipeline.h"
#include "02_system/04_render/VK/VK_Framebuffers.h"
#include "02_system/04_render/VK/VK_Semaphore.h"
#include "02_system/04_render/VK/VK_Fence.h"

#include "01_core/errorHandling/Exceptions.h"

Test_vulkan::Test_vulkan() {
	eventSystem->addListener(this, &Test_vulkan::onAppInit);
	eventSystem->addListener(this, &Test_vulkan::onAppRender);
	eventSystem->addListener(this, &Test_vulkan::onAppCleanUp);
}

void Test_vulkan::onAppInit(AppInitEvent* event) {
	instance = new VK_Instance(&m_settings);
	instance->addRequiredExtension(VK_KHR_SURFACE_EXTENSION_NAME);
	instance->addRequiredExtension("VK_KHR_win32_surface");
	instance->addDesiredExtension(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	instance->addDesiredValidationLayer("VK_LAYER_KHRONOS_validation");
	instance->create();
	instance->printEnabledExtensions();
	instance->printEnabledValidationLayers();

	presentation = new VK_Presentation(this, instance->getId());
	presentation->createSurface();

	device = new VK_Device(instance->getId(),presentation->getSurface());
	device->addRequiredExtension(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
	device->addDesiredValidationLayer("VK_LAYER_KHRONOS_validation");
	device->create();
	device->printEnabledExtensions();
	device->printEnabledValidationLayers();

	presentation->createSwapchain(device);

	renderpass = new VK_Renderpass(device);

	pipeline = new VK_Pipeline(device,renderpass);

	framebuffers = new VK_Framebuffers(device,presentation,renderpass);

	device->createCommandPool();
	device->createCommandBuffers(presentation->getNumImages());
	device->recordCommandBuffers(renderpass,framebuffers,pipeline);

	imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
	renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
	inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
	imagesInFlight.resize(presentation->getNumImages(),VK_NULL_HANDLE);
	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		imageAvailableSemaphores[i]= new VK_Semaphore(device);
		renderFinishedSemaphores[i]= new VK_Semaphore(device);
		inFlightFences[i] = new VK_Fence(device);
	}
}

void Test_vulkan::onAppRender(AppRenderEvent* event){
	VkFence fence = inFlightFences[currentFrame]->getFence();
	CHECK_VK(vkWaitForFences(device->getDevice(), 1, &fence, VK_TRUE, UINT64_MAX),"Failed to wait for fences.");

	uint32_t imageIndex;
	CHECK_VK(vkAcquireNextImageKHR(device->getDevice(), presentation->getSwapchain(), UINT64_MAX, imageAvailableSemaphores[currentFrame]->getSemaphore(), VK_NULL_HANDLE, &imageIndex),"Failed to aquire image.");

	if (imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
		VkFence fence1 = imagesInFlight[imageIndex]->getFence();
		CHECK_VK(vkWaitForFences(device->getDevice(), 1, &fence1, VK_TRUE, UINT64_MAX), "Failed to wait for fences.");
	}
	imagesInFlight[imageIndex] = inFlightFences[currentFrame];

	VkCommandBuffer buffer = device->getCommandBuffer(imageIndex);

	VkSemaphore waitSemaphores[] = { imageAvailableSemaphores[currentFrame]->getSemaphore() };
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	VkSemaphore signalSemaphores[] = { renderFinishedSemaphores[currentFrame ]->getSemaphore()};

	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.pNext = nullptr;
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &buffer;
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	CHECK_VK(vkResetFences(device->getDevice(), 1, &fence),"Failed to reset fence.");

	CHECK_VK(vkQueueSubmit(device->getQueue(), 1, &submitInfo, inFlightFences[currentFrame]->getFence()),"Failed to submit to queue.");

	VkSwapchainKHR swapChains[] = { presentation->getSwapchain() };

	VkPresentInfoKHR presentInfo{};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.pNext = nullptr;
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;
	presentInfo.pImageIndices = &imageIndex;
	presentInfo.pResults = nullptr; // Optional

	CHECK_VK(vkQueuePresentKHR(device->getQueue(), &presentInfo),"Failed to present image.");

	currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void Test_vulkan::onAppCleanUp(AppCleanUpEvent* event) {
	CHECK_VK(vkDeviceWaitIdle(device->getDevice()),"Failed to wait for idle device.");

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		delete imageAvailableSemaphores[i];
		delete renderFinishedSemaphores[i];
		delete inFlightFences[i];
	}

	delete framebuffers;
	delete pipeline;
	delete renderpass;
	presentation->destroySwapchain();
	delete device;
	delete presentation;
	delete instance;
}