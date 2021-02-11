#include "UnitTests.h"

#include <fstream>
#include <vector>

#include "02_system/01_logging/Logger.h"
#include "02_system/02_event/EventSystem.h"
#include "02_system/03_window/WindowSystem.h"
#include "02_system/04_render/GL/VertexAttribute.h"
#include "02_system/04_render/GL_RenderSystem.h"
#include "02_system/04_render/GL_MeshLoader.h"
#include "03_io/parser/Parser.h"
#include "04_math/03_transform/Transform.h"
#include "05_ECS/Entity.h"
#include "05_ECS/Component.h"
#include "06_Geometry/GeometryLoader.h"

Test_openGLContext::Test_openGLContext() {
	eventSystem->addListener(this, &Test_openGLContext::onAppInit);
	eventSystem->addListener(this, &Test_openGLContext::onAppCleanUp);

	eventSystem->addListener(this, &Test_openGLContext::onWindowResize);

	eventSystem->addListener(this, &Test_openGLContext::onKeyPressed);
}

void Test_openGLContext::onAppInit(AppInitEvent* event) {

	GeometryLoader* loader = new GeometryLoader();
	loader->registerGeometry(GeometryType::RECTANGLE, new Rectangle2D());
	loader->registerGeometry(GeometryType::CIRCLE, new Circle2D());
	loader->registerGeometry(GeometryType::CIRCLE_RING, new CircleRing2D());
	loader->registerGeometry(GeometryType::TRIANGLE, new Triangle2D());
	loader->registerGeometry(GeometryType::PLANE, new Plane3D());
	loader->registerGeometry(GeometryType::CUBE, new Cube3D());

	ComponentGeometry* comp;

	comp = new ComponentGeometry(GeometryType::CIRCLE_RING, 32, 300.0f, 0.25f);
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
	loader->loadGeometry(comp,vertices,indices);

	std::vector<Color3f*> colors;
	colors.push_back(new Color3f(0, 1, 0));
	colors.push_back(new Color3f(1, 0, 0));
	colors.push_back(new Color3f(1, 1, 0));

	entity = new Entity2D("Test");
	entity->setRenderType(RenderType::GEOMETRY);
	entity->setTransform(new Transform2D(5,5,500,500,0));
	entity->addComponent(new ComponentMesh(GL_MeshLoader::loadMesh(vertices,indices,VertexAttribute::POS2)));
	entity->addComponent(new ComponentMaterialColors(colors));
	entity->addComponent(comp);
	renderSystem->addEntity(entity);

	comp = new ComponentGeometry(GeometryType::PLANE, 0, 0, 0);
	std::vector<GLfloat> vertices1;
	std::vector<GLuint> indices1;
	loader->loadGeometry(comp, vertices1, indices1);

	plane = new Entity3D("Boden");
	plane->setRenderType(RenderType::COLOR);
	plane->setTransform(new Transform3D(0,0,0,100,100,100,0,0,0));
	plane->addComponent(new ComponentMesh(GL_MeshLoader::loadMesh(vertices1, indices1, VertexAttribute::POS3)));
	plane->addComponent(new ComponentMaterialColor(1, 0, 0));
	plane->addComponent(comp);
	renderSystem->addEntity(plane);

	comp = new ComponentGeometry(GeometryType::CUBE, 0, 0, 0);
	std::vector<GLfloat> vertices2;
	std::vector<GLuint> indices2;
	loader->loadGeometry(comp, vertices2, indices2);

	cube = new Entity3D("Cube");
	cube->setRenderType(RenderType::COLOR);
	cube->setTransform(new Transform3D(0,0, -5, 1, 1, 10, 0,0,0));
	cube->addComponent(new ComponentMesh(GL_MeshLoader::loadMesh(vertices2, indices2, VertexAttribute::POS3)));
	cube->addComponent(new ComponentMaterialColor(1, 1, 0));
	cube->addComponent(comp);
	renderSystem->addEntity(cube);
}

void Test_openGLContext::onAppCleanUp(AppCleanUpEvent* event) {
	delete entity;
	delete plane;
}

void Test_openGLContext::onWindowResize(WindowResizeEvent* event) {
	Loggers::CORE->info("Resize to [%ix%i]", event->m_width, event->m_height);
}

void Test_openGLContext::onKeyPressed(KeyDownEvent* event) {
	if (event->m_key==VK_ESCAPE) {
		eventSystem->postEvent(new WindowCloseEvent());
	}
}