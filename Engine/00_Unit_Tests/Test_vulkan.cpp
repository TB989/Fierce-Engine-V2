#include "UnitTests.h"

#include "02_system/02_event/EventSystem.h"

#include "02_system/04_render/VK/VK_Instance.h"
#include "02_system/04_render/VK/VK_Debug.h"

Test_vulkan::Test_vulkan() {
	eventSystem->addListener(this, &Test_vulkan::onAppInit);
	eventSystem->addListener(this, &Test_vulkan::onAppCleanUp);
}

void Test_vulkan::onAppInit(AppInitEvent* event) {
	instance = new VK_Instance(&m_settings);
	instance->addRequiredExtension("VK_KHR_surface");
	instance->addRequiredExtension("VK_KHR_win32_surface");
	instance->addDesiredExtension(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	instance->addDesiredValidationLayer("VK_LAYER_KHRONOS_validation");

	debug = new VK_Debug();
	instance->linkDebug(debug->getCreateInfo());

	instance->create();

	debug->create(instance->getId());

	instance->printEnabledExtensions();
	instance->printEnabledValidationLayers();
}

void Test_vulkan::onAppCleanUp(AppCleanUpEvent* event) {
	delete debug;
	delete instance;
}