#include "FierceWindow.h"

#include "01_core/errorHandling/Exceptions.h"
#include "02_system/01_logging/Logger.h"

FierceWindow::FierceWindow(LPCWSTR className, LPCWSTR title, EngineSettings settings) {
	CHECK_FIERCE(createWindow(className, title, CW_USEDEFAULT, CW_USEDEFAULT, settings.width, settings.height), "Failed to create window.");
}

FierceWindow::~FierceWindow(){
	CHECK_FIERCE(destroyWindow(),"Failed to destroy window.");
}

FIERCE_ERROR FierceWindow::createWindow(LPCWSTR className, LPCWSTR title, int x, int y, int width, int height) {

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
		r.right - r.left, r.bottom - r.top,
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

void FierceWindow::pollEvents() {
	MSG msg;
	while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
}

void FierceWindow::show() {
	ShowWindow(windowHandle, SW_SHOW);
	UpdateWindow(windowHandle);
}