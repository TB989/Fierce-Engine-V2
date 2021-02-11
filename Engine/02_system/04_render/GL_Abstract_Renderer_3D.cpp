#include "GL_Abstract_Renderer_3D.h"

#include "05_ECS/Entity.h"
#include "04_math/02_matrix/Matrix.h"

void GL_Abstract_Renderer_3D::render() {
	prepareRendering();
	for (Entity3D* entity : entities) {
		prepareEntity(entity);
		renderEntity(entity);
	}
	finishRendering();
}

void GL_Abstract_Renderer_3D::prepareRendering() {
	pipeline->bind();
}

void GL_Abstract_Renderer_3D::prepareEntity(Entity3D* entity) {
	Mat4 modelMatrix;
	modelMatrix.setToIdentity();
	modelMatrix.transform(entity->getTransform());
	pipeline->loadUniform("modelMatrix", &modelMatrix);
}

void GL_Abstract_Renderer_3D::renderEntity(Entity3D* entity) {
	ComponentMesh* mesh = (ComponentMesh*)(entity->getComponent(ComponentType::MESH));
	mesh->render();
}

void GL_Abstract_Renderer_3D::finishRendering() {
	pipeline->unbind();
}
