#pragma once

#include "core/Core.h"
#include "Common.h"

#include "core/EngineSettings.h"
#include "events/EventSystem.h"
#include "window/WindowSystem.h"

class Test_logging : public Core {

public:
	Test_logging();
	void onAppInit(AppInitEvent* event);
};

class Test_engineConfig : public Core {
public:
	Test_engineConfig();
	void onAppInit(AppInitEvent* event);
private:
	EngineSettings m_settings = {};
};

class Test_eventSystem : public Core {
public:
	Test_eventSystem();
	void onAppInit(AppInitEvent* event);
	void onAppUpdate(AppUpdateEvent* event);
	void onAppRender(AppRenderEvent* event);
	void onAppCleanUp(AppCleanUpEvent* event);
};

class Test_window : public Core {
public:
	Test_window();
	void onAppInit(AppInitEvent* event);
	void onAppUpdate(AppUpdateEvent* event);
	void onAppCleanUp(AppCleanUpEvent* event);

	void onWindowResize(WindowResizeEvent* event);
private:
	EngineSettings m_settings = {};
	WindowSystem* windowSystem;
	FierceWindow* window;
};

class Test_openGLContext : public Core {
public:
	Test_openGLContext();
	void onAppInit(AppInitEvent* event);
	void onAppUpdate(AppUpdateEvent* event);
	void onAppCleanUp(AppCleanUpEvent* event);

	void onWindowResize(WindowResizeEvent* event);
private:
	EngineSettings m_settings = {};
	WindowSystem* windowSystem;
	FierceWindow* window;
};