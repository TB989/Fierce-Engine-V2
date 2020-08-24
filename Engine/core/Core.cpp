#include "Core.h"

Core::Core() {
	eventSystem = new EventSystem();
}

Core::~Core() {
	delete eventSystem;
}

void Core::run() {
	coreInit();
	coreUpdate();
	coreRender();
	coreCleanUp();
}

void Core::coreInit() {
	eventSystem->postEvent(new AppInitEvent());
}

void Core::coreUpdate() {
	eventSystem->postEvent(new AppUpdateEvent(0));
}

void Core::coreRender() {
	eventSystem->postEvent(new AppRenderEvent());
}

void Core::coreCleanUp() {
	eventSystem->postEvent(new AppCleanUpEvent());
}