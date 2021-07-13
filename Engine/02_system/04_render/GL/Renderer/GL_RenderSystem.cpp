#include "GL_RenderSystem.h"

#include "01_core/EngineSettings.h"
#include "01_core/Core.h"
#include "02_system/04_render/GL/Objects/GL_Shader.h"
#include "02_system/04_render/GL/Objects/GL_Pipeline.h"
#include "02_system/04_render/GL/Objects/VertexAttribute.h"
#include "02_system/04_render/GL/Objects/GL_Context.h"
#include "02_system/04_render/GL/Renderer/GL_Renderer.h"
#include "02_system/04_render/01_Abstract/RenderType.h"
#include "04_math/02_matrix/Matrix.h"
#include "05_ECS/Entity.h"

GL_RenderSystem::GL_RenderSystem(Core* app, EngineSettings* settings, Entity3D* camera) {
	m_camera = camera;

	context = new GL_Context(app);

	Mat4 orthographicProjectionMatrix = Mat4();
	orthographicProjectionMatrix.setToOrthographicProjection(settings->width, settings->height, -1.0f, 1.0f);

	Mat4 perspectiveProjectionMatrix = Mat4();
	perspectiveProjectionMatrix.setToPerspectiveProjection((float)(settings->width) / (float)(settings->height), 60.0f, 0.1f, 1000.0f);

	loadShaders();
	loadPipelines();
	loadRenderers();

	//Load orthographic projection matrix
	for (std::pair<std::string, GL_Renderer*> renderer : renderers2D) {
		//renderer.second->getPipeline()->bind();
		//renderer.second->getPipeline()->loadUniform("projectionMatrix", &orthographicProjectionMatrix);
		//renderer.second->getPipeline()->unbind();
	}

	//Load perspective projection matrix
	for (std::pair<std::string, GL_Renderer*> renderer : renderers3D) {
		//renderer.second->getPipeline()->bind();
		//renderer.second->getPipeline()->loadUniform("projectionMatrix", &perspectiveProjectionMatrix);
		//renderer.second->getPipeline()->unbind();
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}

GL_RenderSystem::~GL_RenderSystem() {
	for (auto it = renderers2D.begin(); it != renderers2D.end(); it++) {
		delete it->second;
	}
	for (auto it = pipelines.begin(); it != pipelines.end(); it++) {
		delete it->second;
	}
	for (auto it = shaders.begin(); it != shaders.end(); it++) {
		delete it->second;
	}
}

void GL_RenderSystem::render() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Mat4 viewMatrix;
	viewMatrix.setToView(m_camera->getTransform());

	//Render 3D
	for (std::pair<std::string, GL_Renderer*> renderer : renderers3D) {
		//renderer.second->getPipeline()->bind();
		//renderer.second->getPipeline()->loadUniform("viewMatrix", &viewMatrix);
		//renderer.second->getPipeline()->unbind();
		//renderer.second->render();
	}

	//Render 2D
	glDisable(GL_DEPTH_TEST);
	for (std::pair<std::string, GL_Renderer*> renderer : renderers2D) {
		//renderer.second->render();
	}
	glEnable(GL_DEPTH_TEST);

	//Swap buffers
	context->swapBuffers();
}

void GL_RenderSystem::loadShaders() {
	//Vertex shaders
	shaders["Shader_Color2D.vs"] = new GL_Shader("Shader_Color2D.vs");
	shaders["Shader_Color3D.vs"] = new GL_Shader("Shader_Color3D.vs");

	//Fragment shaders
	shaders["Shader_Color.fs"] = new GL_Shader("Shader_Color.fs");
}

void GL_RenderSystem::loadPipelines() {
	GL_Pipeline* pipeline;

	//Color2D
	pipeline= new GL_Pipeline("Color_2D", shaders["Shader_Color2D.vs"], shaders["Shader_Color.fs"]);
	pipeline->addVertexAttribute(VertexAttribute::POS2);
	pipeline->addUniformLocation("projectionMatrix");
	pipeline->addUniformLocation("modelMatrix");
	pipeline->addUniformLocation("color");
	pipeline->create();
	pipelines["Color2D"] = pipeline;

	//Color3D
	pipeline = new GL_Pipeline("Color_3D", shaders["Shader_Color3D.vs"], shaders["Shader_Color.fs"]);
	pipeline->addVertexAttribute(VertexAttribute::POS3);
	pipeline->addUniformLocation("projectionMatrix");
	pipeline->addUniformLocation("viewMatrix");
	pipeline->addUniformLocation("modelMatrix");
	pipeline->addUniformLocation("color");
	pipeline->create();
	pipelines["Color3D"] = pipeline;
}

void GL_RenderSystem::loadRenderers(){

}