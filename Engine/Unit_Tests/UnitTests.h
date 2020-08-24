#pragma once

#include "core/Core.h"
#include "Common.h"

#include "core/EngineSettings.h"

#include "events/EventSystem.h"

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