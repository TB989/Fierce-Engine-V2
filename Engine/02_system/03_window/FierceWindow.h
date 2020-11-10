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
enum FIERCE_ERROR;

class FierceWindow {
public:
	FierceWindow(LPCWSTR className, LPCWSTR title, EngineSettings settings);
	~FierceWindow();

	void pollEvents();
	void show();

	HWND getHandle() { return windowHandle; }
private:
	FIERCE_ERROR createWindow(LPCWSTR className, LPCWSTR title, int x, int y, int width, int height);
	FIERCE_ERROR destroyWindow();
private:
	HWND windowHandle=nullptr;
};