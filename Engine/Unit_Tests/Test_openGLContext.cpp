#include "UnitTests.h"
#include "parser/Parser.h"

Test_openGLContext::Test_openGLContext() {
	eventSystem->addListener(this, &Test_openGLContext::onAppInit);
	eventSystem->addListener(this, &Test_openGLContext::onAppUpdate);
	eventSystem->addListener(this, &Test_openGLContext::onAppCleanUp);

	eventSystem->addListener(this, &Test_openGLContext::onWindowResize);
}

void Test_openGLContext::onAppInit(AppInitEvent* event) {
	std::map<std::string, std::string> settings = Parser::parsePropertiesFile("C:/Users/Tobias/Desktop/GameEngine/Engine/Engine.ini");
	m_settings.parse(settings);

	windowSystem = new WindowSystem(this, m_settings);
	window = windowSystem->createWindow();
	window->show();
}

void Test_openGLContext::onAppUpdate(AppUpdateEvent* event) {
	window->pollEvents();
}

void Test_openGLContext::onAppCleanUp(AppCleanUpEvent* event) {
	delete window;
	delete windowSystem;
}

void Test_openGLContext::onWindowResize(WindowResizeEvent* event) {
	Loggers::CORE->info("Resize to [%ix%i]", event->m_width, event->m_height);
}