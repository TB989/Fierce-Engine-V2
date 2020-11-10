#include "WindowSystem.h"

#include "01_core/Core.h"
#include "01_core/errorHandling/Exceptions.h"
#include "02_system/01_logging/Logger.h"
#include "02_system/02_event/EventSystem.h"
#include "02_system/02_event/Event.h"

#include "FierceWindow.h"

LRESULT CALLBACK wndProcFierceWindow(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	FierceWindow* window = static_cast<FierceWindow*>(GetProp(hWnd, L"windowHandle"));
	WindowSystem* windowSystem = static_cast<WindowSystem*>(GetProp(hWnd, L"windowSystem"));

	switch (message) {
	case WM_CLOSE:
		windowSystem->postEvent(new WindowCloseEvent());
		break;
	case WM_SIZE:
		windowSystem->postEvent(new WindowResizeEvent(LOWORD(lParam), HIWORD(lParam)));
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK wndProcFierceDummyWindow(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(hWnd, message, wParam, lParam);
}

WindowSystem::WindowSystem(Core* app, EngineSettings settings){
	m_app = app;
	m_settings = settings;
	hInstance= GetModuleHandle(NULL);

	app->eventSystem->addListener(this,&WindowSystem::onHandleRequested);

	CHECK_FIERCE(registerWindowClass(fierceWindowClassName,wndProcFierceWindow), "Failed to register window class for fierce window.");
	CHECK_FIERCE(registerWindowClass(fierceDummyWindowClassName,wndProcFierceDummyWindow), "Failed to register window class for fierce dummy window.");

	m_dummyWindow = new FierceWindow(fierceDummyWindowClassName, L"FierceDummyWindow", m_settings);
	SetProp(m_dummyWindow->getHandle(), L"windowSystem", this);
}

WindowSystem::~WindowSystem(){
	delete m_dummyWindow;
	CHECK_FIERCE(unregisterWindowClass(fierceWindowClassName), "Failed to unregister window class for fierce window.");
	CHECK_FIERCE(unregisterWindowClass(fierceDummyWindowClassName), "Failed to unregister window class for fierce dummy window.");
}

FierceWindow* WindowSystem::createWindow(){
	if (m_window==nullptr) {
		m_window = new FierceWindow(fierceWindowClassName, L"FierceWindow", m_settings);
		SetProp(m_window->getHandle(), L"windowSystem", this);
		return m_window;
	}
	else {
		return m_window;
	}
}

void WindowSystem::onHandleRequested(WindowRequestHandleEvent* evt){
	if (evt->m_dummy) {
		m_app->eventSystem->postEvent(new WindowSendHandleEvent(true,m_dummyWindow->getHandle()));
	}
	else {
		m_app->eventSystem->postEvent(new WindowSendHandleEvent(false, m_window->getHandle()));
	}
}

FIERCE_ERROR WindowSystem::registerWindowClass(LPCWSTR className, WNDPROC wndProc){
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = wndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = className;
	wc.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wc)) {
		return FE_WINDOW_ERROR;
	}
	return FE_NO_ERROR;
}

FIERCE_ERROR WindowSystem::unregisterWindowClass(LPCWSTR className){
	if (!UnregisterClass(className, hInstance)) {
		return FE_WINDOW_ERROR;
	}
	return FE_NO_ERROR;
}