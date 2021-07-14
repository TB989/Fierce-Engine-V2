#include "UnitTests.h"

#include "02_system/01_logging/Logger.h"
#include "02_system/02_event/EventSystem.h"
#include "02_system/04_render/01_Abstract/RenderType.h"
#include "02_system/04_render/02_GL/01_Objects/Fierce_GL.h"
#include "02_system/04_render/02_GL/01_Objects/GL_MeshLoader.h"
#include "02_system/04_render/02_GL/01_Objects/VertexAttribute.h"
#include "04_math/03_transform/Transform.h"
#include "04_math/04_color/Color.h"
#include "05_ECS/EntityManager.h"
#include "05_ECS/ComponentManager.h"
#include "05_ECS/Component.h"
#include "06_Geometry/GeometryLoader.h"

Test_openGLContext::Test_openGLContext() {
	eventSystem->addListener(this, &Test_openGLContext::onAppInit);
	eventSystem->addListener(this, &Test_openGLContext::onAppCleanUp);

	eventSystem->addListener(this, &Test_openGLContext::onWindowResize);

	eventSystem->addListener(this, &Test_openGLContext::onKeyPressed);
}

void Test_openGLContext::onAppInit(AppInitEvent* event) {
	//Init ECS
	ent=new EntityManager(50);
	comp = new ComponentManager();
	comp->registerComponent<Transform2D>(50);
	comp->registerComponent<Transform3D>(50);
	comp->registerComponent<RenderType>(50);
	comp->registerComponent<ComponentGeometry>(50);
	comp->registerComponent<ComponentMesh>(50);
	comp->registerComponent<ComponentMaterialColors>(50);

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

	//Define color arrays
	std::vector<Color3f*> colors;
	colors.push_back(new Color3f(1, 0, 0));
	colors.push_back(new Color3f(0, 1, 0));
	colors.push_back(new Color3f(0, 0, 1));
	colors.push_back(new Color3f(1, 1, 0));
	colors.push_back(new Color3f(0, 1, 1));
	colors.push_back(new Color3f(1, 0, 1));

	std::vector<Color3f*> colors2;
	colors2.push_back(new Color3f(0, 0.5f, 0));

	//Create rectangle
	rectangle = ent->createEntity();
	comp->addComponent(rectangle, RenderType::GEOMETRY);
	comp->addComponent(rectangle, Transform2D(5, 5, 100, 100, 0));
	comp->addComponent(rectangle, ComponentMaterialColors(colors));
	comp->addComponent(rectangle, ComponentGeometry(GeometryType::RECTANGLE, 0, 0, 0, 0));

	//Create triangle
	triangle = ent->createEntity();
	comp->addComponent(triangle, RenderType::GEOMETRY);
	comp->addComponent(triangle, Transform2D(110, 5, 100, 100, 0));
	comp->addComponent(triangle, ComponentMaterialColors(colors));
	comp->addComponent(triangle, ComponentGeometry(GeometryType::TRIANGLE, 0, 0, 0, 0));

	//Create circle
	circle = ent->createEntity();
	comp->addComponent(circle, RenderType::GEOMETRY);
	comp->addComponent(circle, Transform2D(215, 5, 100, 100, 0));
	comp->addComponent(circle, ComponentMaterialColors(colors));
	comp->addComponent(circle, ComponentGeometry(GeometryType::CIRCLE, 32, 360.0f, 0, 0));

	//Create circleRing
	circleRing = ent->createEntity();
	comp->addComponent(circleRing, RenderType::GEOMETRY);
	comp->addComponent(circleRing, Transform2D(320, 5, 100, 100, 0));
	comp->addComponent(circleRing, ComponentMaterialColors(colors));
	comp->addComponent(circleRing, ComponentGeometry(GeometryType::CIRCLE_RING, 32, 360.0f, 0.25f, 0));

	//Create plane
	plane = ent->createEntity();
	comp->addComponent(plane, RenderType::GEOMETRY);
	comp->addComponent(plane, Transform3D(0, 0, 0, 100, 100, 100, 0, 0, 0));
	comp->addComponent(plane, ComponentMaterialColors(colors2));
	comp->addComponent(plane, ComponentGeometry(GeometryType::PLANE, 0, 0, 0, 0));

	//Create cube
	cube = ent->createEntity();
	comp->addComponent(cube, RenderType::GEOMETRY);
	comp->addComponent(cube, Transform3D(0, 0.5f, -5, 1, 1, 1, 0, 0, 0));
	comp->addComponent(cube, ComponentMaterialColors(colors));
	comp->addComponent(cube, ComponentGeometry(GeometryType::CUBE, 0, 0, 0, 0));

	//Create cylinder
	cylinder = ent->createEntity();
	comp->addComponent(cylinder, RenderType::GEOMETRY);
	comp->addComponent(cylinder, Transform3D(3, 0.5f, -5, 1, 1, 1, 0, 0, 0));
	comp->addComponent(cylinder, ComponentMaterialColors(colors));
	comp->addComponent(cylinder, ComponentGeometry(GeometryType::CYLINDER, 32, 270.0f, 0, 0));

	//Create hollow cylinder
	hollowCylinder = ent->createEntity();
	comp->addComponent(hollowCylinder, RenderType::GEOMETRY);
	comp->addComponent(hollowCylinder, Transform3D(6, 0.5f, -5, 1, 1, 1, 0, 0, 0));
	comp->addComponent(hollowCylinder, ComponentMaterialColors(colors));
	comp->addComponent(hollowCylinder, ComponentGeometry(GeometryType::HOLLOW_CYLINDER, 32, 270.0f, 0.25f, 0));

	//Create cone
	cone = ent->createEntity();
	comp->addComponent(cone, RenderType::GEOMETRY);
	comp->addComponent(cone, Transform3D(9, 0.5f, -5, 1, 1, 1, 0, 0, 0));
	comp->addComponent(cone, ComponentMaterialColors(colors));
	comp->addComponent(cone, ComponentGeometry(GeometryType::CONE, 32, 270.0f, 0, 0));

	//Create sphere
	sphere = ent->createEntity();
	comp->addComponent(sphere, RenderType::GEOMETRY);
	comp->addComponent(sphere, Transform3D(12, 0.5f, -5, 1, 1, 1, 0, 0, 0));
	comp->addComponent(sphere, ComponentMaterialColors(colors));
	comp->addComponent(sphere, ComponentGeometry(GeometryType::SPHERE, 32, 360.0f, 0, 12));

	//Load geometries
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
	loader->loadGeometry(comp->getComponent<ComponentGeometry>(rectangle), vertices, indices);
	comp->addComponent(rectangle, ComponentMesh(GL_MeshLoader::loadMesh(vertices, indices, VertexAttribute::POS2)));
	vertices.clear();
	indices.clear();
	loader->loadGeometry(comp->getComponent<ComponentGeometry>(triangle), vertices, indices);
	comp->addComponent(triangle, ComponentMesh(GL_MeshLoader::loadMesh(vertices, indices, VertexAttribute::POS2)));
	vertices.clear();
	indices.clear();
	loader->loadGeometry(comp->getComponent<ComponentGeometry>(circle), vertices, indices);
	comp->addComponent(circle, ComponentMesh(GL_MeshLoader::loadMesh(vertices, indices, VertexAttribute::POS2)));
	vertices.clear();
	indices.clear();
	loader->loadGeometry(comp->getComponent<ComponentGeometry>(circleRing), vertices, indices);
	comp->addComponent(circleRing, ComponentMesh(GL_MeshLoader::loadMesh(vertices, indices, VertexAttribute::POS2)));
	vertices.clear();
	indices.clear();
	loader->loadGeometry(comp->getComponent<ComponentGeometry>(plane), vertices, indices);
	comp->addComponent(plane, ComponentMesh(GL_MeshLoader::loadMesh(vertices, indices, VertexAttribute::POS3)));
	vertices.clear();
	indices.clear();
	loader->loadGeometry(comp->getComponent<ComponentGeometry>(cube), vertices, indices);
	comp->addComponent(cube, ComponentMesh(GL_MeshLoader::loadMesh(vertices, indices, VertexAttribute::POS3)));
	vertices.clear();
	indices.clear();
	loader->loadGeometry(comp->getComponent<ComponentGeometry>(cylinder), vertices, indices);
	comp->addComponent(cylinder, ComponentMesh(GL_MeshLoader::loadMesh(vertices, indices, VertexAttribute::POS3)));
	vertices.clear();
	indices.clear();
	loader->loadGeometry(comp->getComponent<ComponentGeometry>(hollowCylinder), vertices, indices);
	comp->addComponent(hollowCylinder, ComponentMesh(GL_MeshLoader::loadMesh(vertices, indices, VertexAttribute::POS3)));
	vertices.clear();
	indices.clear();
	loader->loadGeometry(comp->getComponent<ComponentGeometry>(cone), vertices, indices);
	comp->addComponent(cone, ComponentMesh(GL_MeshLoader::loadMesh(vertices, indices, VertexAttribute::POS3)));
	vertices.clear();
	indices.clear();
	loader->loadGeometry(comp->getComponent<ComponentGeometry>(sphere), vertices, indices);
	comp->addComponent(sphere, ComponentMesh(GL_MeshLoader::loadMesh(vertices, indices, VertexAttribute::POS3)));

	//Add to render system
	/**renderSystem->addEntity(rectangle);
	renderSystem->addEntity(triangle);
	renderSystem->addEntity(circle);
	renderSystem->addEntity(circleRing);
	renderSystem->addEntity(plane);
	renderSystem->addEntity(cube);
	renderSystem->addEntity(cylinder);
	renderSystem->addEntity(hollowCylinder);
	renderSystem->addEntity(cone);
	renderSystem->addEntity(sphere);*/
}

void Test_openGLContext::onAppCleanUp(AppCleanUpEvent* event) {
	removeComponents2D(rectangle);
	ent->destroyEntity(rectangle);
	removeComponents2D(triangle);
	ent->destroyEntity(triangle);
	removeComponents2D(circle);
	ent->destroyEntity(circle);
	removeComponents2D(circleRing);
	ent->destroyEntity(circleRing);

	removeComponents3D(plane);
	ent->destroyEntity(plane);
	removeComponents3D(cube);
	ent->destroyEntity(cube);
	removeComponents3D(cylinder);
	ent->destroyEntity(cylinder);
	removeComponents3D(hollowCylinder);
	ent->destroyEntity(hollowCylinder);
	removeComponents3D(cone);
	ent->destroyEntity(cone);
	removeComponents3D(sphere);
	ent->destroyEntity(sphere);

	comp->unregisterComponent<Transform2D>();
	comp->unregisterComponent<Transform3D>();
	comp->unregisterComponent<RenderType>();
	comp->unregisterComponent<ComponentGeometry>();
	comp->unregisterComponent<ComponentMesh>();
	comp->unregisterComponent<ComponentMaterialColors>();
	delete comp;
	delete ent;
}

void Test_openGLContext::onWindowResize(WindowResizeEvent* event) {
	Loggers::CORE->info("Resize to [%ix%i]", event->m_width, event->m_height);
}

void Test_openGLContext::onKeyPressed(KeyDownEvent* event) {
	if (event->m_key==VK_ESCAPE) {
		eventSystem->postEvent(new WindowCloseEvent());
	}
}

void Test_openGLContext::removeComponents2D(int entity){
	comp->removeComponent<Transform2D>(entity);
	comp->removeComponent<RenderType>(entity);
	comp->removeComponent<ComponentGeometry>(entity);
	comp->removeComponent<ComponentMesh>(entity);
	comp->removeComponent<ComponentMaterialColors>(entity);
}

void Test_openGLContext::removeComponents3D(int entity){
	comp->removeComponent<Transform3D>(entity);
	comp->removeComponent<RenderType>(entity);
	comp->removeComponent<ComponentGeometry>(entity);
	comp->removeComponent<ComponentMesh>(entity);
	comp->removeComponent<ComponentMaterialColors>(entity);
}