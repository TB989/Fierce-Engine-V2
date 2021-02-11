#include "GL_Abstract_Renderer_2D.h"

#include "05_ECS/Entity.h"
#include "04_math/02_matrix/Matrix.h"

void GL_Abstract_Renderer_2D::render(){
	prepareRendering();
	for (Entity2D* entity : entities) {
		prepareEntity(entity);
		renderEntity(entity);
	}
	finishRendering();
}

void GL_Abstract_Renderer_2D::prepareRendering(){
	pipeline->bind();
}

void GL_Abstract_Renderer_2D::prepareEntity(Entity2D* entity){
	Mat4 modelMatrix;
	modelMatrix.setToIdentity();
	modelMatrix.transform(entity->getTransform());
	pipeline->loadUniform("modelMatrix", &modelMatrix);
}

void GL_Abstract_Renderer_2D::renderEntity(Entity2D* entity){
	ComponentMesh* mesh = (ComponentMesh*)(entity->getComponent(ComponentType::MESH));
	mesh->render();
}

void GL_Abstract_Renderer_2D::finishRendering(){
	pipeline->unbind();
}