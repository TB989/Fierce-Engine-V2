#include "UnitTests.h"

#include "02_system/02_event/EventSystem.h"

#include "02_system/04_render/VK/VK_Instance.h"
#include "02_system/04_render/VK/VK_Device.h"

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

	device = new VK_Device(instance->getId());
	device->addRequiredExtension(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
	device->addDesiredValidationLayer("VK_LAYER_KHRONOS_validation");
	device->create();
	device->printEnabledExtensions();
	device->printEnabledValidationLayers();
}

void Test_vulkan::onAppCleanUp(AppCleanUpEvent* event) {
	delete device;
	delete instance;
}