#pragma once

#include "core\Core.h"
#include "Common.h"

class Test_logging : public Core {

protected:
	virtual void init();
	virtual void update();
	virtual void render();
	virtual void cleanUp();
};