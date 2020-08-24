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

protected:
	EventSystem* eventSystem;
};