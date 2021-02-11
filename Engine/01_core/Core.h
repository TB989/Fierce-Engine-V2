#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "01_core/EngineSettings.h"

/* SystemIncludes*/

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/
class EventSystem;
class WindowSystem;
class GL_RenderSystem;
class FierceWindow;
struct WindowCloseEvent;
struct MouseMoveEvent;
struct KeyDownEvent;
class Entity3D;

class Core {
private:
	void coreInit();
	void coreUpdate();
	void coreRender();
	void coreCleanUp();
public:
	Core();
	~Core();

	void run();

public:
	EngineSettings m_settings;
	EventSystem* eventSystem=nullptr;
	WindowSystem* windowSystem=nullptr;
	GL_RenderSystem* renderSystem = nullptr;

private:
	bool running = false;

	void onWindowClosed(WindowCloseEvent* event);

	bool first = true;
	int m_x_alt=0;
	int m_y_alt=0;
	void onMouseMoved(MouseMoveEvent* event);
	void onKeyPressed(KeyDownEvent* event);

	FierceWindow* m_window=nullptr;

	Entity3D* camera = nullptr;
};