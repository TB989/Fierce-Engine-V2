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
	Entity2D* entity=nullptr;
	Entity3D* plane = nullptr;
	Entity3D* cube = nullptr;
};

class Test_math : public Core {
public:
	Test_math();
	void onAppInit(AppInitEvent* event);
};