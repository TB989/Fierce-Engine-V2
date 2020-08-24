#pragma once

struct Event {};

struct AppInitEvent : public Event {};
struct AppUpdateEvent : public Event {
	AppUpdateEvent(float dt) : m_dt{ dt } {}
	float m_dt;
};
struct AppRenderEvent : public Event {};
struct AppCleanUpEvent : public Event {};