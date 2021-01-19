#include "UnitTests.h"

#include <fstream>

#include "02_system/01_logging/Logger.h"
#include "02_system/02_event/EventSystem.h"
#include "02_system/03_window/WindowSystem.h"
#include "02_system/04_render/GL_RenderSystem.h"
#include "02_system/04_render/GL/GL_Context.h"
#include "02_system/04_render/GL/GL_Shader.h"
#include "02_system/04_render/GL/GL_Pipeline.h"
#include "02_system/04_render/GL/GL_VBO.h"
#include "02_system/04_render/GL/GL_VAO.h"
#include "02_system/04_render/GL/Fierce_GL.h"
#include "04_math/02_matrix/Matrix.h"
#include "04_math/03_transform/Transform.h"
#include "03_io/parser/Parser.h"
#include "05_ECS/Entity.h"
#include "05_ECS/Component.h"

#include "02_system/04_render/GL/VertexAttribute.h"

#include "06_Geometry/GeometryLoader.h"

Test_openGLContext::Test_openGLContext() {
	eventSystem->addListener(this, &Test_openGLContext::onAppInit);
	eventSystem->addListener(this, &Test_openGLContext::onAppCleanUp);

	eventSystem->addListener(this, &Test_openGLContext::onWindowResize);
}

void Test_openGLContext::onAppInit(AppInitEvent* event) {

	GeometryLoader* loader = new GeometryLoader();
	loader->registerGeometry(GeometryType::RECTANGLE, new Rectangle2D());
	loader->registerGeometry(GeometryType::CIRCLE, new Circle2D());
	loader->registerGeometry(GeometryType::CIRCLE_RING, new CircleRing2D());
	loader->registerGeometry(GeometryType::TRIANGLE, new Triangle2D());

	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
	loader->loadGeometry(new ComponentGeometry(GeometryType::TRIANGLE,32,360.0f,0.25f),vertices,indices);

	GL_VBO* vbo = new GL_VBO(GL_ARRAY_BUFFER);
	vbo->loadData(sizeof(GLfloat)*vertices.size(), vertices.data(), GL_STATIC_DRAW);

	GL_VBO* vboi = new GL_VBO(GL_ELEMENT_ARRAY_BUFFER);
	vboi->loadData(sizeof(GLuint)*indices.size(), indices.data(), GL_STATIC_DRAW);

	GL_VAO* vao = new GL_VAO(vbo,vboi);
	vao->addVertexAttribute(VertexAttribute::POS2);

	entity = new Entity2D("Test");
	entity->setTransform(new Transform2D(5,5,500,500,0));
	entity->addComponent(new ComponentMesh(vao));
	renderSystem->addEntity(entity);
}

void Test_openGLContext::onAppCleanUp(AppCleanUpEvent* event) {
	delete entity;
	delete vao;
	delete vbo;
}

void Test_openGLContext::onWindowResize(WindowResizeEvent* event) {
	Loggers::CORE->info("Resize to [%ix%i]", event->m_width, event->m_height);
}