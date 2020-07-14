#pragma once

#include "core\Core.h"

class FierceEngine : public Core {

protected:
	virtual void init();
	virtual void update();
	virtual void render();
	virtual void cleanUp();
};