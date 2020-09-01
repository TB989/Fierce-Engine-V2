#pragma once

struct Event {};

struct AppInitEvent : public Event {};
struct AppUpdateEvent : public Event {
	AppUpdateEvent(float dt) : m_dt{ dt } {}
	float m_dt;
};
struct AppRenderEvent : public Event {};
struct AppCleanUpEvent : public Event {};

struct WindowCloseEvent : public Event {};
struct WindowResizeEvent : public Event {
	WindowResizeEvent(int width, int height) :m_width{ width }, m_height{ height }{}
	int m_width;
	int m_height;
};