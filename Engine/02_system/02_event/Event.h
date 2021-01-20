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

struct Event {};

struct AppInitEvent : public Event {};
struct AppUpdateEvent : public Event {
	AppUpdateEvent(float dt) : m_dt{ dt } {}
	float m_dt;
};
struct AppRenderEvent : public Event {};
struct AppCleanUpEvent : public Event {};

struct WindowRequestHandleEvent : public Event {
	WindowRequestHandleEvent(bool dummy) :m_dummy{ dummy } {}
	bool m_dummy;
};
struct WindowSendHandleEvent : public Event {
	WindowSendHandleEvent(bool dummy, HWND handle) :m_dummy{ dummy }, m_handle{ handle } {}
	bool m_dummy;
	HWND m_handle;
};
struct WindowCloseEvent : public Event {};
struct WindowResizeEvent : public Event {
	WindowResizeEvent(int width, int height) :m_width{ width }, m_height{ height }{}
	int m_width;
	int m_height;
};

struct KeyDownEvent : public Event {
	KeyDownEvent(WPARAM key) :m_key{ key } {}
	WPARAM m_key;
};

struct KeyUpEvent : public Event {
	KeyUpEvent(WPARAM key) :m_key{ key } {}
	WPARAM m_key;
};

struct CharEvent : public Event {
	CharEvent(char character) :m_character{ character } {}
	char m_character;
};