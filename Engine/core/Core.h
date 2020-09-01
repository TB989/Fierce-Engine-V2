#pragma once

#include "Common.h"
#include "events/EventSystem.h"

class Core {
private:
	void coreInit();
	void coreUpdate();
	void coreRender();
	void coreCleanUp();
public:
	Core();
	~Core();

	void run();

public:
	EventSystem* eventSystem;

private:
	bool running=false;

	void onWindowClosed(WindowCloseEvent* event);
};