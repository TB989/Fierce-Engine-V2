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
class FierceWindow;
struct WindowCloseEvent;

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

private:
	bool running = false;

	void onWindowClosed(WindowCloseEvent* event);

	FierceWindow* m_window=nullptr;
};