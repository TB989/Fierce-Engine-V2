#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "01_core/EngineSettings.h"

/* SystemIncludes*/
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/
class Core;
class FierceWindow;
enum FIERCE_ERROR;
struct WindowRequestHandleEvent;

class WindowSystem {
public:
	WindowSystem(Core* app, EngineSettings* settings);
	~WindowSystem();

	template<typename EventType>
	void postEvent(EventType* evnt) {
		m_app->eventSystem->postEvent(evnt);
	}

	FierceWindow* createWindow();

private:
	FIERCE_ERROR registerWindowClass(LPCWSTR className, WNDPROC wndProc);
	FIERCE_ERROR unregisterWindowClass(LPCWSTR className);

	void onHandleRequested(WindowRequestHandleEvent* evt);
private:
	Core* m_app=nullptr;
	EngineSettings* m_settings = {};

	HINSTANCE hInstance=nullptr;
	LPCWSTR fierceWindowClassName = L"FierceWindow";
	LPCWSTR fierceDummyWindowClassName = L"FierceDummyWindow";

	FierceWindow* m_window=nullptr;
	FierceWindow* m_dummyWindow=nullptr;
};