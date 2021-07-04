#include "UnitTests.h"

#include "02_system/02_event/EventSystem.h"

#include "02_system/04_render/VK/VK_Instance.h"
#include "02_system/04_render/VK/VK_Device.h"
#include "02_system/04_render/VK/VK_Presentation.h"
#include "02_system/04_render/VK/VK_Pipeline.h"

Test_vulkan::Test_vulkan() {
	eventSystem->addListener(this, &Test_vulkan::onAppInit);
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

	pipeline = new VK_Pipeline(device);
}

void Test_vulkan::onAppCleanUp(AppCleanUpEvent* event) {
	delete pipeline;
	presentation->destroySwapchain();
	delete device;
	delete presentation;
	delete instance;
}