#include "GL_Renderer_Color3D.h"

#include "02_system/01_logging/Logger.h"
#include "02_system/04_render/GL/Objects/GL_Pipeline.h"
#include "04_math/02_matrix/Matrix.h"
#include "05_ECS/Entity.h"

GL_Renderer_Color3D::GL_Renderer_Color3D(GL_Pipeline* pipeline){
	m_pipeline = pipeline;
}

void GL_Renderer_Color3D::render() {
	m_pipeline->bind();
	for (Entity3D* entity : entities) {
		//Prepare entity
		Mat4 modelMatrix;
		modelMatrix.setToIdentity();
		modelMatrix.transform(entity->getTransform());
		m_pipeline->loadUniform("modelMatrix", &modelMatrix);

		//Load color
		ComponentMaterialColor* color = (ComponentMaterialColor*)(entity->getComponent(ComponentType::MATERIAL_COLOR));
		m_pipeline->loadUniform("color", color->getR(), color->getG(), color->getB());

		//Render entity
		ComponentMesh* mesh = (ComponentMesh*)(entity->getComponent(ComponentType::MESH));
		mesh->render();
	}
	m_pipeline->unbind();
}