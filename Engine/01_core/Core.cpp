#include "Core.h"

#include "02_system/01_logging/Logger.h"
#include "02_system/02_event/EventSystem.h"
#include "02_system/02_event/Event.h"
#include "02_system/03_window/WindowSystem.h"
#include "02_system/03_window/FierceWindow.h"
#include "02_system/04_render/GL_RenderSystem.h"
#include "03_io/parser/Parser.h"

Core::Core() {
	Loggers::CORE->info("Loading engine settings.");
	std::map<std::string, std::string> settings = Parser::parsePropertiesFile("C:/Users/Tobias/Desktop/GameEngine/Engine/Engine.ini");
	m_settings.parse(settings);
	
	Loggers::CORE->info("Starting event system.");
	eventSystem = new EventSystem();
	eventSystem->addListener(this, &Core::onWindowClosed);
}

Core::~Core() {
	if (m_settings.windowMode != HEADLESS) {
		Loggers::CORE->info("Stopping render system.");
		delete renderSystem;

		Loggers::CORE->info("Stopping window system.");
		delete windowSystem;
	}
	Loggers::CORE->info("Stopping event system.");
	delete eventSystem;
}

void Core::run() {
	coreInit();

	running = false;
	if (m_settings.windowMode != HEADLESS) {
		m_window->show();
		Loggers::CORE->info("Starting game loop.");
		running = true;
	}

	while (running) {
		m_window->pollEvents();
		coreUpdate();
		renderSystem->render();
		coreRender();
	}
	coreCleanUp();
}

void Core::coreInit() {
	if (m_settings.windowMode != HEADLESS) {
		Loggers::CORE->info("Starting window system.");
		windowSystem = new WindowSystem(this, &m_settings);
		m_window = windowSystem->getWindow();

		Loggers::CORE->info("Starting render system.");
		renderSystem = new GL_RenderSystem(this, &m_settings);
	}

	Loggers::CORE->info("Starting engine.");
	eventSystem->postEvent(new AppInitEvent());
}

void Core::coreUpdate() {
	eventSystem->postEvent(new AppUpdateEvent(0));
}

void Core::coreRender() {
	eventSystem->postEvent(new AppRenderEvent());
}

void Core::coreCleanUp() {
	Loggers::CORE->info("Stopping engine.");
	eventSystem->postEvent(new AppCleanUpEvent());
}

void Core::onWindowClosed(WindowCloseEvent* event) {
	running = false;
}