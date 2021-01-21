#include "GL_RenderSystem.h"

#include "01_core/Core.h"
#include "02_system/04_render/GL/GL_Context.h"
#include "02_system/04_render/GL/GL_Shader.h"
#include "02_system/04_render/GL/GL_Pipeline.h"
#include "02_system/04_render/GL/GL_VAO.h"
#include "02_system/04_render/GL/GL_VBO.h"
#include "02_system/04_render/GL/VertexAttribute.h"
#include "04_math/02_matrix/Matrix.h"
#include "04_math/03_transform/Transform.h"
#include "05_ECS/Entity.h"
#include "05_ECS/Component.h"

GL_RenderSystem::GL_RenderSystem(Core* app, EngineSettings* settings){
	context = new GL_Context(app);

	orthographicProjectionMatrix = new Mat4();
	orthographicProjectionMatrix->setToOrthographicProjection(settings->width, settings->height, -1.0f, 1.0f);

	loadShaders();
	loadPipelines();
}

GL_RenderSystem::~GL_RenderSystem(){
	entities2D.clear();
	entities3D.clear();

	//Delete pipelines
	std::map<std::string, GL_Pipeline*>::iterator it;
	for (it = pipelines.begin();it!=pipelines.end();++it) {
		delete it->second;
	}

	//Delete shaders
	std::map<std::string, GL_Shader*>::iterator it1;
	for (it1 = shaders.begin(); it1 != shaders.end(); ++it1) {
		delete it1->second;
	}

	delete context;
}

void GL_RenderSystem::addEntity(Entity2D* entity){
	entities2D.push_back(entity);
}

void GL_RenderSystem::addEntity(Entity3D* entity){
	entities3D.push_back(entity);
}

void GL_RenderSystem::render(){
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	pipelines["MyFirstPipeline"]->bind();

	Mat4 modelMatrix;
	for (Entity2D* entity:entities2D) {
		modelMatrix.transform(entity->getTransform());
		pipelines["MyFirstPipeline"]->loadUniform("modelMatrix", &modelMatrix);

		ComponentMesh* mesh = (ComponentMesh*)(entity->getComponent(""));
		mesh->render();
	}

	pipelines["MyFirstPipeline"]->unbind();

	context->swapBuffers();
}

void GL_RenderSystem::loadShaders(){
	shaders["MyFirstShader.vs"]= new GL_Shader("MyFirstShader.vs");
	shaders["MyFirstShader.fs"] = new GL_Shader("MyFirstShader.fs");
}

void GL_RenderSystem::loadPipelines(){
	GL_Pipeline* pipeline = new GL_Pipeline("MyFirstPipeline", shaders["MyFirstShader.vs"], shaders["MyFirstShader.fs"]);
	pipeline->addVertexAttribute(VertexAttribute::POS2);
	pipeline->addUniformLocation("projectionMatrix");
	pipeline->addUniformLocation("modelMatrix");
	pipeline->create();
	pipeline->bind();
	pipeline->loadUniform("projectionMatrix", orthographicProjectionMatrix);
	pipeline->unbind();
	pipelines["MyFirstPipeline"] = pipeline;
}