#pragma once

#include "Common.h"

class Core {
protected:
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void cleanUp() = 0;
private:
	void coreInit();
	void coreUpdate();
	void coreRender();
	void coreCleanUp();
public:
	void run();
};