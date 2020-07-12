#include "Core.h"

void Core::run() {
	coreInit();
	coreUpdate();
	coreRender();
	coreCleanUp();
}

void Core::coreInit() {
	init();
}

void Core::coreUpdate() {
	update();
}

void Core::coreRender() {
	render();
}

void Core::coreCleanUp() {
	cleanUp();
}