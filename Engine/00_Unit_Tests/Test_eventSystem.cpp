#include "UnitTests.h"

#include "02_system/01_logging/Logger.h"
#include "02_system/02_event/EventSystem.h"

Test_eventSystem::Test_eventSystem(){
	eventSystem->addListener(this, &Test_eventSystem::onAppInit);
	eventSystem->addListener(this, &Test_eventSystem::onAppUpdate);
	eventSystem->addListener(this, &Test_eventSystem::onAppRender);
	eventSystem->addListener(this, &Test_eventSystem::onAppCleanUp);
}

void Test_eventSystem::onAppInit(AppInitEvent * event) {
	Loggers::CORE->info("On app init!");
}

void Test_eventSystem::onAppUpdate(AppUpdateEvent* event) {
	Loggers::CORE->info("On app update!");
}

void Test_eventSystem::onAppRender(AppRenderEvent* event) {
	Loggers::CORE->info("On app render!");
}

void Test_eventSystem::onAppCleanUp(AppCleanUpEvent* event) {
	Loggers::CORE->info("On app clean up!");
}