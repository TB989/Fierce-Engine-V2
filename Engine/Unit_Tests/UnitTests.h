#pragma once

#include "core/Core.h"
#include "Common.h"

#include "core/EngineSettings.h"

class Test_logging : public Core {

protected:
	virtual void init();
	virtual void update();
	virtual void render();
	virtual void cleanUp();
};

class Test_engineConfig : public Core {

protected:
	virtual void init();
	virtual void update();
	virtual void render();
	virtual void cleanUp();
private:
	EngineSettings m_settings = {};
};