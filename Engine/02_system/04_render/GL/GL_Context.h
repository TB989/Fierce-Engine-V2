#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/

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
struct WindowSendHandleEvent;

class GL_Context {
public:
	GL_Context(Core* core);
	~GL_Context();

	void swapBuffers();
private:
	void getWindowHandles(Core* core);

	void createDummyContext();
	void deleteDummyContext();

	void createContext();
	void deleteContext();
private:
	void onHandleReceived(WindowSendHandleEvent* evt);
private:
	HWND dummyHandle = nullptr;
	HDC dummyHDC = nullptr;
	HGLRC dummyContext = nullptr;

	HWND windowHandle = nullptr;
	HDC openGLHDC = nullptr;
	HGLRC openGLContext = nullptr;
};