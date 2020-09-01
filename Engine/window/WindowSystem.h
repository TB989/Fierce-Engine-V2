#pragma once

#include "Common.h"
#include "core/Core.h"
#include <Windows.h>
#include "core/EngineSettings.h"

class FierceWindow {
public:
	FierceWindow(LPCWSTR className, LPCWSTR title, EngineSettings settings);

	void pollEvents();
	void show();

	HWND getHandle() { return windowHandle; }
private:
	FIERCE_ERROR createWindow(LPCWSTR className, LPCWSTR title, int x, int y, int width, int height);
	FIERCE_ERROR destroyWindow();
private:
	HWND windowHandle;
};

class WindowSystem {
public:
	WindowSystem(Core* app, EngineSettings settings);
	~WindowSystem();

	FierceWindow* createWindow();
	FierceWindow* createDummyWindow();

	template<typename EventType>
	void postEvent(EventType* evnt) {
		m_app->eventSystem->postEvent(evnt);
	}
private:
	FIERCE_ERROR registerWindowClass(LPCWSTR className, WNDPROC wndProc);
	FIERCE_ERROR unregisterWindowClass(LPCWSTR className);
private:
	Core* m_app;
	EngineSettings m_settings;

	HINSTANCE hInstance;
	LPCWSTR fierceWindowClassName = L"FierceWindow";
	LPCWSTR fierceDummyWindowClassName = L"FierceDummyWindow";
};