#include "GL_RenderSystem.h"

#include "01_core/Core.h"
#include "05_ECS/Entity.h"
#include "05_ECS/Component.h"

#include "02_system/04_render/GL/GL_Context.h"
#include "04_math/02_matrix/Matrix.h"
#include "02_system/04_render/GL/GL_Pipeline.h"
#include "04_math/03_transform/Transform.h"
#include "02_system/01_logging/Logger.h"

#include "02_system/04_render/GL_Abstract_Renderer.h"
#include "02_system/04_render/GL_Abstract_Renderer_2D.h"
#include "02_system/04_render/GL_Abstract_Renderer_3D.h"
#include "GL_Renderer_Color3D.h"
#include "GL_Renderer_Color2D.h"
#include "GL_Renderer_Geometry2D.h"
#include "GL_Renderer_Geometry3D.h"

#include "01_core/errorHandling/Exceptions.h"

GL_RenderSystem::GL_RenderSystem(Core* app, EngineSettings* settings, Entity3D* camera){
	m_camera = camera;

	context = new GL_Context(app);

	Mat4 orthographicProjectionMatrix = Mat4();
	orthographicProjectionMatrix.setToOrthographicProjection(settings->width, settings->height, -1.0f, 1.0f);

	Mat4 perspectiveProjectionMatrix = Mat4();
	perspectiveProjectionMatrix.setToPerspectiveProjection((float)(settings->width)/(float)(settings->height), 60.0f,0.1f, 1000.0f);

	addRenderers();

	//Load orthographic projection matrix
	for (std::pair<RenderType, GL_Abstract_Renderer_2D*> renderer : renderers2D) {
		renderer.second->getPipeline()->bind();
		renderer.second->getPipeline()->loadUniform("projectionMatrix", &orthographicProjectionMatrix);
		renderer.second->getPipeline()->unbind();
	}

	//Load perspective projection matrix
	for (std::pair<RenderType, GL_Abstract_Renderer_3D*> renderer : renderers3D) {
		renderer.second->getPipeline()->bind();
		renderer.second->getPipeline()->loadUniform("projectionMatrix", &perspectiveProjectionMatrix);
		renderer.second->getPipeline()->unbind();
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}

GL_RenderSystem::~GL_RenderSystem(){
	
	//Delete 2D renderers
	for (std::pair<RenderType, GL_Abstract_Renderer_2D*> renderer : renderers2D){
		delete renderer.second;
	}

	//Delete 3D renderers
	for (std::pair<RenderType, GL_Abstract_Renderer_3D*> renderer : renderers3D) {
		delete renderer.second;
	}

	delete context;
}

void GL_RenderSystem::addEntity(Entity2D* entity){
	switch (entity->getRenderType()) {
	case RenderType::COLOR:
		renderers2D[RenderType::COLOR]->addEntity(entity);
		break;
	case RenderType::GEOMETRY:
		renderers2D[RenderType::GEOMETRY]->addEntity(entity);
		break;
	}
}

void GL_RenderSystem::addEntity(Entity3D* entity){
	switch (entity->getRenderType()) {
	case RenderType::COLOR:
		renderers3D[RenderType::COLOR]->addEntity(entity);
		break;
	case RenderType::GEOMETRY:
		renderers3D[RenderType::GEOMETRY]->addEntity(entity);
		break;
	}
}

void GL_RenderSystem::render(){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Mat4 viewMatrix;
	viewMatrix.setToView(m_camera->getTransform());

	//Render 3D
	for (std::pair<RenderType, GL_Abstract_Renderer_3D*> renderer : renderers3D) {
		renderer.second->getPipeline()->bind();
		renderer.second->getPipeline()->loadUniform("viewMatrix", &viewMatrix);
		renderer.second->getPipeline()->unbind();
		renderer.second->render();
	}

	//Render 2D
	glDisable(GL_DEPTH_TEST);
	for (std::pair<RenderType, GL_Abstract_Renderer_2D*> renderer : renderers2D) {
		renderer.second->render();
	}
	glEnable(GL_DEPTH_TEST);

	//Swap buffers
	context->swapBuffers();
}

void GL_RenderSystem::addRenderers(){
	//Renderer 3D
	renderers3D[RenderType::COLOR]=new GL_Renderer_Color3D();
	renderers3D[RenderType::GEOMETRY] = new GL_Renderer_Geometry3D();

	//Renderer 2D
	renderers2D[RenderType::COLOR] = new GL_Renderer_Color2D();
	renderers2D[RenderType::GEOMETRY] = new GL_Renderer_Geometry2D();
}