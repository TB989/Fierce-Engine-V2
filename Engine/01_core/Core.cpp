#include "Core.h"

#include "02_system/01_logging/Logger.h"
#include "02_system/02_event/EventSystem.h"
#include "02_system/02_event/Event.h"
#include "02_system/03_window/WindowSystem.h"
#include "02_system/03_window/FierceWindow.h"
#include "02_system/04_render/GL_RenderSystem.h"
#include "03_io/parser/Parser.h"
#include "05_ECS/Entity.h"
#include "04_math/03_transform/Transform.h"
#include "04_math/01_vector/Vector.h"

#define _USE_MATH_DEFINES
#include <math.h>

Core::Core() {
	Loggers::CORE->info("Loading engine settings.");
	std::map<std::string, std::string> settings = Parser::parsePropertiesFile("C:/Users/Tobias/Desktop/FierceEngine/Engine/Engine.ini");
	m_settings.parse(settings);
	
	Loggers::CORE->info("Starting event system.");
	eventSystem = new EventSystem();
	eventSystem->addListener(this, &Core::onWindowClosed);
	eventSystem->addListener(this, &Core::onMouseMoved);
	eventSystem->addListener(this, &Core::onKeyPressed);
}

Core::~Core() {
	if (m_settings.windowMode != HEADLESS) {
		Loggers::CORE->info("Stopping render system.");
		switch (m_settings.api) {
		case API::OPEN_GL:
			delete renderSystem;
			break;
		case API::VULKAN:
			break;
		}

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
		if (m_settings.api == API::OPEN_GL) {
			renderSystem->render();
		}
		coreRender();
	}
	coreCleanUp();
}

void Core::coreInit() {
	if (m_settings.windowMode != HEADLESS) {
		Loggers::CORE->info("Starting window system.");
		windowSystem = new WindowSystem(this, &m_settings);
		m_window = windowSystem->getWindow();

		Loggers::CORE->info("Creating camera.");
		camera = new Entity3D("Camera");
		camera->setTransform(new Transform3D(0, 2, 0, 1,1,1, 0, 0, 0));

		Loggers::CORE->info("Starting render system.");
		switch (m_settings.api) {
		case API::OPEN_GL:
			renderSystem = new GL_RenderSystem(this, &m_settings, camera);
			break;
		case API::VULKAN:
			break;
		}
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

void Core::onMouseMoved(MouseMoveEvent* event){
	if (first) {
		m_x_alt = event->m_x;
		m_y_alt = event->m_y;
		first = false;
		return;
	}

	int dx = m_x_alt - event->m_x;
	int dy = m_y_alt - event->m_y;

	Vector3f* angles=camera->getTransform()->getRotation();

	float angleX = angles->getX() - 0.3f * dy;
	if (angleX>45.0f) {
		angleX = 45.0f;
	}
	if (angleX < -45.0f) {
		angleX = -45.0f;
	}
	angles->setX(angleX);

	float angleY = angles->getY() - 0.3f * dx;
	angles->setY(angleY);

	m_x_alt = event->m_x;
	m_y_alt = event->m_y;
}

void Core::onKeyPressed(KeyDownEvent* event) {
	if (event->m_key == 'W') {
		Vector3f* angles = camera->getTransform()->getRotation();
		Vector3f* position = camera->getTransform()->getPosition();
		float angleY = angles->getY();
		float s = sin(M_PI / 180.0f * angleY);
		float c = cos(M_PI / 180.0f * angleY);
		position->setX(position->getX() + s*0.3f);
		position->setZ(position->getZ() - c * 0.3f);
	}

	if (event->m_key == 'S') {
		Vector3f* angles = camera->getTransform()->getRotation();
		Vector3f* position = camera->getTransform()->getPosition();
		float angleY = angles->getY();
		float s = sin(M_PI / 180.0f * angleY);
		float c = cos(M_PI / 180.0f * angleY);
		position->setX(position->getX() - s * 0.3f);
		position->setZ(position->getZ() + c * 0.3f);
	}
}