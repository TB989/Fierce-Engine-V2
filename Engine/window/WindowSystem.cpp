#include "WindowSystem.h"

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

	CHECK_FIERCE(registerWindowClass(fierceWindowClassName,wndProcFierceWindow), "Failed to register window class for fierce window.");
	CHECK_FIERCE(registerWindowClass(fierceDummyWindowClassName,wndProcFierceDummyWindow), "Failed to register window class for fierce dummy window.");
}

WindowSystem::~WindowSystem(){
	CHECK_FIERCE(unregisterWindowClass(fierceWindowClassName), "Failed to unregister window class for fierce window.");
	CHECK_FIERCE(unregisterWindowClass(fierceDummyWindowClassName), "Failed to unregister window class for fierce dummy window.");
}

FierceWindow* WindowSystem::createWindow(){
	FierceWindow* window= new FierceWindow(fierceWindowClassName,L"FierceWindow",m_settings);
	SetProp(window->getHandle(), L"windowSystem", this);
	return window;
}

FierceWindow* WindowSystem::createDummyWindow(){
	FierceWindow* window = new FierceWindow(fierceDummyWindowClassName, L"FierceDummyWindow", m_settings);
	SetProp(window->getHandle(), L"windowSystem", this);
	return window;
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





FierceWindow::FierceWindow(LPCWSTR className, LPCWSTR title, EngineSettings settings){
	CHECK_FIERCE(createWindow(className,title,CW_USEDEFAULT,CW_USEDEFAULT,settings.width,settings.height),"Failed to create window.");
}

FIERCE_ERROR FierceWindow::createWindow(LPCWSTR className, LPCWSTR title,int x, int y, int width, int height) {

	RECT r = RECT();
	r.top = 0;
	r.bottom = height;
	r.left = 0;
	r.right = width;
	if (!AdjustWindowRectEx(&r, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_APPWINDOW | WS_EX_TOPMOST)) {
		return FE_WINDOW_ERROR;
	}

	windowHandle = CreateWindowEx(
		WS_EX_APPWINDOW | WS_EX_TOPMOST,
		className,
		title,
		WS_OVERLAPPEDWINDOW,
		0, 0,
		r.right-r.left,r.bottom-r.top,
		NULL,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	if (!windowHandle) {
		return FE_WINDOW_ERROR;
	}

	SetProp(windowHandle, L"windowHandle", this);
	return FE_NO_ERROR;
}

FIERCE_ERROR FierceWindow::destroyWindow() {
	if (!DestroyWindow(windowHandle)) {
		return FE_WINDOW_ERROR;
	}
	return FE_NO_ERROR;
}

void FierceWindow::pollEvents(){
	MSG msg;
	while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
}

void FierceWindow::show(){
	ShowWindow(windowHandle, SW_SHOW);
	UpdateWindow(windowHandle);
}