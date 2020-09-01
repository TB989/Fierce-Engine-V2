#include "UnitTests.h"
#include "parser/Parser.h"

Test_window::Test_window() {
	eventSystem->addListener(this, &Test_window::onAppInit);
	eventSystem->addListener(this, &Test_window::onAppUpdate);
	eventSystem->addListener(this, &Test_window::onAppCleanUp);

	eventSystem->addListener(this,&Test_window::onWindowResize);
}

void Test_window::onAppInit(AppInitEvent* event) {
	std::map<std::string, std::string> settings = Parser::parsePropertiesFile("C:/Users/Tobias/Desktop/GameEngine/Engine/Engine.ini");
	m_settings.parse(settings);

	windowSystem = new WindowSystem(this, m_settings);
	window = windowSystem->createWindow();
	window->show();
}

void Test_window::onAppUpdate(AppUpdateEvent* event) {
	window->pollEvents();
}

void Test_window::onAppCleanUp(AppCleanUpEvent* event) {
	delete window;
	delete windowSystem;
}

void Test_window::onWindowResize(WindowResizeEvent* event) {
	Loggers::CORE->info("Resize to [%ix%i]", event->m_width, event->m_height);
}