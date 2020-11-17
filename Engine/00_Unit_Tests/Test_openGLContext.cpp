#include "UnitTests.h"

#include <fstream>

#include "02_system/01_logging/Logger.h"
#include "02_system/02_event/EventSystem.h"
#include "02_system/03_window/WindowSystem.h"
#include "02_system/04_render/GL/GL_Context.h"
#include "02_system/04_render/GL/GL_Shader.h"
#include "02_system/04_render/GL/GL_Pipeline.h"
#include "02_system/04_render/GL/GL_VBO.h"
#include "02_system/04_render/GL/GL_VAO.h"
#include "02_system/04_render/GL/Fierce_GL.h"
#include "03_io/parser/Parser.h"

Test_openGLContext::Test_openGLContext() {
	eventSystem->addListener(this, &Test_openGLContext::onAppInit);
	eventSystem->addListener(this, &Test_openGLContext::onAppUpdate);
	eventSystem->addListener(this, &Test_openGLContext::onAppCleanUp);

	eventSystem->addListener(this, &Test_openGLContext::onWindowResize);
}

void Test_openGLContext::onAppInit(AppInitEvent* event) {
	context = new GL_Context(this);

	static const GLfloat g_vertex_buffer_data[] = {
	   -1.0f, -1.0f, 0.0f,
	   1.0f, -1.0f, 0.0f,
	   0.0f,  1.0f, 0.0f,
	};

	vbo = new GL_VBO(GL_ARRAY_BUFFER);
	vbo->loadData(sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	vao = new GL_VAO(vbo);
	vao->vertexAttribPointer(0, 3, GL_FLOAT);

	vertexShader=new GL_Shader("MyFirstShader.vs");
	fragmentShader=new GL_Shader("MyFirstShader.fs");

	pipeline = new GL_Pipeline("MyFirstPipeline",vertexShader,fragmentShader);
}

void Test_openGLContext::onAppUpdate(AppUpdateEvent* event) {
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	pipeline->bind();
	vao->bind();
	vao->draw();
	vao->unbind();
	pipeline->unbind();

	context->swapBuffers();
}

void Test_openGLContext::onAppCleanUp(AppCleanUpEvent* event) {
	delete pipeline;
	delete vertexShader;
	delete fragmentShader;
	delete vao;
	delete vbo;
	delete context;
}

void Test_openGLContext::onWindowResize(WindowResizeEvent* event) {
	Loggers::CORE->info("Resize to [%ix%i]", event->m_width, event->m_height);
}