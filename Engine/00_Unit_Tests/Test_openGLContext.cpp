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

#include "01_core/errorHandling/Exceptions.h"

Test_openGLContext::Test_openGLContext() {
	eventSystem->addListener(this, &Test_openGLContext::onAppInit);
	eventSystem->addListener(this, &Test_openGLContext::onAppCleanUp);

	eventSystem->addListener(this, &Test_openGLContext::onWindowResize);

	eventSystem->addListener(this, &Test_openGLContext::onKeyPressed);
}

void Test_openGLContext::onAppInit(AppInitEvent* event) {

	//Init geometry loader
	GeometryLoader* loader = new GeometryLoader();
	loader->registerGeometry(GeometryType::RECTANGLE, new Rectangle2D());
	loader->registerGeometry(GeometryType::CIRCLE, new Circle2D());
	loader->registerGeometry(GeometryType::CIRCLE_RING, new CircleRing2D());
	loader->registerGeometry(GeometryType::TRIANGLE, new Triangle2D());
	loader->registerGeometry(GeometryType::PLANE, new Plane3D());
	loader->registerGeometry(GeometryType::CUBE, new Cube3D());
	loader->registerGeometry(GeometryType::CYLINDER, new Cylinder3D());
	loader->registerGeometry(GeometryType::HOLLOW_CYLINDER, new HollowCylinder3D());
	loader->registerGeometry(GeometryType::CONE, new Cone3D());
	loader->registerGeometry(GeometryType::SPHERE, new Sphere3D());

	//Color array
	std::vector<Color3f*> colors;
	colors.push_back(new Color3f(1, 0, 0));
	colors.push_back(new Color3f(0, 1, 0));
	colors.push_back(new Color3f(0, 0, 1));
	colors.push_back(new Color3f(1, 1, 0));
	colors.push_back(new Color3f(0, 1, 1));
	colors.push_back(new Color3f(1, 0, 1));

	std::vector<Color3f*> colors2;
	colors2.push_back(new Color3f(0, 0.5f, 0));

	//Create geometries
	ComponentGeometry* geo_rect = new ComponentGeometry(GeometryType::RECTANGLE, 0, 0, 0,0);
	ComponentGeometry* geo_tria = new ComponentGeometry(GeometryType::TRIANGLE, 0, 0, 0,0);
	ComponentGeometry* geo_circle = new ComponentGeometry(GeometryType::CIRCLE, 32, 360.0f, 0,0);
	ComponentGeometry* geo_circle_ring = new ComponentGeometry(GeometryType::CIRCLE_RING, 32, 360.0f, 0.25f,0);
	ComponentGeometry* geo_plane = new ComponentGeometry(GeometryType::PLANE, 0, 0, 0,0);
	ComponentGeometry* geo_cube = new ComponentGeometry(GeometryType::CUBE, 0, 0, 0,0);
	ComponentGeometry* geo_cylinder = new ComponentGeometry(GeometryType::CYLINDER, 32, 270.0f, 0,0);
	ComponentGeometry* geo_hollowCylinder = new ComponentGeometry(GeometryType::HOLLOW_CYLINDER, 32, 270.0f, 0.25f,0);
	ComponentGeometry* geo_cone = new ComponentGeometry(GeometryType::CONE, 32, 270.0f, 0,0);
	ComponentGeometry* geo_sphere = new ComponentGeometry(GeometryType::SPHERE, 32, 360.0f, 0, 12);

	//Create rectangle
	rectangle = new Entity2D("Rectangle");
	rectangle->setRenderType(RenderType::GEOMETRY);
	rectangle->setTransform(new Transform2D(5, 5, 100, 100, 0));
	rectangle->addComponent(new ComponentMaterialColors(colors));
	rectangle->addComponent(geo_rect);

	//Create triangle
	triangle = new Entity2D("Triangle");
	triangle->setRenderType(RenderType::GEOMETRY);
	triangle->setTransform(new Transform2D(110, 5, 100, 100, 0));
	triangle->addComponent(new ComponentMaterialColors(colors));
	triangle->addComponent(geo_tria);

	//Create circle
	circle = new Entity2D("Circle");
	circle->setRenderType(RenderType::GEOMETRY);
	circle->setTransform(new Transform2D(215, 5, 100, 100, 0));
	circle->addComponent(new ComponentMaterialColors(colors));
	circle->addComponent(geo_circle);

	//Create circleRing
	circleRing = new Entity2D("Circle ring");
	circleRing->setRenderType(RenderType::GEOMETRY);
	circleRing->setTransform(new Transform2D(320, 5, 100, 100, 0));
	circleRing->addComponent(new ComponentMaterialColors(colors));
	circleRing->addComponent(geo_circle_ring);

	//Create plane
	plane = new Entity3D("Boden");
	plane->setRenderType(RenderType::GEOMETRY);
	plane->setTransform(new Transform3D(0, 0, 0, 100, 100, 100, 0, 0, 0));
	plane->addComponent(new ComponentMaterialColors(colors2));
	plane->addComponent(geo_plane);

	//Create cube
	cube = new Entity3D("Cube");
	cube->setRenderType(RenderType::GEOMETRY);
	cube->setTransform(new Transform3D(0, 0.5f, -5, 1, 1, 1, 0, 0, 0));
	cube->addComponent(new ComponentMaterialColors(colors));
	cube->addComponent(geo_cube);

	//Create cylinder
	cylinder = new Entity3D("Cylinder");
	cylinder->setRenderType(RenderType::GEOMETRY);
	cylinder->setTransform(new Transform3D(3, 0.5f, -5, 1, 1, 1, 0, 0, 0));
	cylinder->addComponent(new ComponentMaterialColors(colors));
	cylinder->addComponent(geo_cylinder);

	//Create hollow cylinder
	hollowCylinder = new Entity3D("Hollow Cylinder");
	hollowCylinder->setRenderType(RenderType::GEOMETRY);
	hollowCylinder->setTransform(new Transform3D(6, 0.5f, -5, 1, 1, 1, 0, 0, 0));
	hollowCylinder->addComponent(new ComponentMaterialColors(colors));
	hollowCylinder->addComponent(geo_hollowCylinder);

	//Create cone
	cone = new Entity3D("Cone");
	cone->setRenderType(RenderType::GEOMETRY);
	cone->setTransform(new Transform3D(9, 0.5f, -5, 1, 1, 1, 0, 0, 0));
	cone->addComponent(new ComponentMaterialColors(colors));
	cone->addComponent(geo_cone);

	//Create sphere
	sphere = new Entity3D("Sphere");
	sphere->setRenderType(RenderType::GEOMETRY);
	sphere->setTransform(new Transform3D(12, 0.5f, -5, 1, 1, 1, 0, 0, 0));
	sphere->addComponent(new ComponentMaterialColors(colors));
	sphere->addComponent(geo_sphere);

	//Load geometries
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
	loader->loadGeometry(geo_rect, vertices, indices);
	rectangle->addComponent(new ComponentMesh(GL_MeshLoader::loadMesh(vertices, indices, VertexAttribute::POS2)));
	vertices.clear();
	indices.clear();
	loader->loadGeometry(geo_tria, vertices, indices);
	triangle->addComponent(new ComponentMesh(GL_MeshLoader::loadMesh(vertices, indices, VertexAttribute::POS2)));
	vertices.clear();
	indices.clear();
	loader->loadGeometry(geo_circle, vertices, indices);
	circle->addComponent(new ComponentMesh(GL_MeshLoader::loadMesh(vertices, indices, VertexAttribute::POS2)));
	vertices.clear();
	indices.clear();
	loader->loadGeometry(geo_circle_ring, vertices, indices);
	circleRing->addComponent(new ComponentMesh(GL_MeshLoader::loadMesh(vertices, indices, VertexAttribute::POS2)));
	vertices.clear();
	indices.clear();
	loader->loadGeometry(geo_plane, vertices, indices);
	plane->addComponent(new ComponentMesh(GL_MeshLoader::loadMesh(vertices, indices, VertexAttribute::POS3)));
	vertices.clear();
	indices.clear();
	loader->loadGeometry(geo_cube, vertices, indices);
	cube->addComponent(new ComponentMesh(GL_MeshLoader::loadMesh(vertices, indices, VertexAttribute::POS3)));
	vertices.clear();
	indices.clear();
	loader->loadGeometry(geo_cylinder, vertices, indices);
	cylinder->addComponent(new ComponentMesh(GL_MeshLoader::loadMesh(vertices, indices, VertexAttribute::POS3)));
	vertices.clear();
	indices.clear();
	loader->loadGeometry(geo_hollowCylinder, vertices, indices);
	hollowCylinder->addComponent(new ComponentMesh(GL_MeshLoader::loadMesh(vertices, indices, VertexAttribute::POS3)));
	vertices.clear();
	indices.clear();
	loader->loadGeometry(geo_cone, vertices, indices);
	cone->addComponent(new ComponentMesh(GL_MeshLoader::loadMesh(vertices, indices, VertexAttribute::POS3)));
	vertices.clear();
	indices.clear();
	loader->loadGeometry(geo_sphere, vertices, indices);
	sphere->addComponent(new ComponentMesh(GL_MeshLoader::loadMesh(vertices, indices, VertexAttribute::POS3)));


	//Add to render system
	renderSystem->addEntity(rectangle);
	renderSystem->addEntity(triangle);
	renderSystem->addEntity(circle);
	renderSystem->addEntity(circleRing);
	renderSystem->addEntity(plane);
	renderSystem->addEntity(cube);
	renderSystem->addEntity(cylinder);
	renderSystem->addEntity(hollowCylinder);
	renderSystem->addEntity(cone);
	renderSystem->addEntity(sphere);
}

void Test_openGLContext::onAppCleanUp(AppCleanUpEvent* event) {
	delete rectangle;
	delete triangle;
	delete circle;
	delete circleRing;

	delete plane;
	delete cube;
	delete cylinder;
	delete hollowCylinder;
	delete sphere;
}

void Test_openGLContext::onWindowResize(WindowResizeEvent* event) {
	Loggers::CORE->info("Resize to [%ix%i]", event->m_width, event->m_height);
}

void Test_openGLContext::onKeyPressed(KeyDownEvent* event) {
	if (event->m_key==VK_ESCAPE) {
		eventSystem->postEvent(new WindowCloseEvent());
	}
}