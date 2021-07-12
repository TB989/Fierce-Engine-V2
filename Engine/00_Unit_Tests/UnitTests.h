#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "01_core/Core.h"
#include "02_system/02_event/Event.h"

/* SystemIncludes*/

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/
class Entity2D;
class Entity3D;

class Test_logging : public Core {

public:
	Test_logging();
	void onAppInit(AppInitEvent* event);
};

class Test_engineConfig : public Core {
public:
	Test_engineConfig();
	void onAppInit(AppInitEvent* event);
private:
	EngineSettings m_settings = {};
};

class Test_eventSystem : public Core {
public:
	Test_eventSystem();
	void onAppInit(AppInitEvent* event);
	void onAppUpdate(AppUpdateEvent* event);
	void onAppRender(AppRenderEvent* event);
	void onAppCleanUp(AppCleanUpEvent* event);
};

class Test_openGLContext : public Core {
public:
	Test_openGLContext();
	void onAppInit(AppInitEvent* event);
	void onAppCleanUp(AppCleanUpEvent* event);

	void onWindowResize(WindowResizeEvent* event);

	void onKeyPressed(KeyDownEvent* event);
private:
	Entity2D* rectangle=nullptr;
	Entity2D* triangle = nullptr;
	Entity2D* circle = nullptr;
	Entity2D* circleRing = nullptr;

	Entity3D* plane = nullptr;
	Entity3D* cube = nullptr;
	Entity3D* cylinder = nullptr;
	Entity3D* hollowCylinder = nullptr;
	Entity3D* cone = nullptr;
	Entity3D* sphere = nullptr;
};

class Test_math : public Core {
public:
	Test_math();
	void onAppInit(AppInitEvent* event);
};

class VK_Instance;
class VK_Device;
class VK_Presentation;
class VK_Renderpass;
class VK_Pipeline;
class VK_Framebuffers;
class VK_Semaphore;
class VK_Fence;

class Test_vulkan : public Core {
public:
	Test_vulkan();
	void onAppInit(AppInitEvent* event);
	void onAppRender(AppRenderEvent* event);
	void onAppCleanUp(AppCleanUpEvent* event);
private:
	size_t currentFrame = 0;
	const int MAX_FRAMES_IN_FLIGHT = 2;

	VK_Instance* instance;
	VK_Device* device;
	VK_Presentation* presentation;
	VK_Renderpass* renderpass;
	VK_Pipeline* pipeline;
	VK_Framebuffers* framebuffers;

	std::vector<VK_Semaphore*> imageAvailableSemaphores;
	std::vector<VK_Semaphore*> renderFinishedSemaphores;
	std::vector<VK_Fence*> inFlightFences;
	std::vector<VK_Fence*> imagesInFlight;
};