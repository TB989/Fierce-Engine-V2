#include "GL_Renderer_Geometry3D.h"

#include "02_system/04_render/GL/GL_Shader.h"
#include "02_system/04_render/GL/GL_Pipeline.h"
#include "02_system/04_render/GL/VertexAttribute.h"

GL_Renderer_Geometry3D::GL_Renderer_Geometry3D() {
	loadShaders();
	createPipeline();
}

void GL_Renderer_Geometry3D::loadShaders() {
	vertexShader = new GL_Shader("Shader_Color3D.vs");
	fragmentShader = new GL_Shader("Shader_Color.fs");
}

void GL_Renderer_Geometry3D::createPipeline() {
	pipeline = new GL_Pipeline("Geometry_3D", vertexShader, fragmentShader);
	pipeline->addVertexAttribute(VertexAttribute::POS3);
	pipeline->addUniformLocation("projectionMatrix");
	pipeline->addUniformLocation("viewMatrix");
	pipeline->addUniformLocation("modelMatrix");
	pipeline->addUniformLocation("color");
	pipeline->create();
}

void GL_Renderer_Geometry3D::renderEntity(Entity3D* entity) {
	ComponentMaterialColors* colors = (ComponentMaterialColors*)(entity->getComponent(ComponentType::MATERIAL_COLORS));
	colors->reset();
	ComponentMesh* mesh = (ComponentMesh*)(entity->getComponent(ComponentType::MESH));
	Color3f* color;
	ComponentGeometry* geo = (ComponentGeometry*)(entity->getComponent(ComponentType::GEOMETRY));
	int count = 0;

	switch (geo->getType()) {
	case PLANE:
		color = colors->getNextColor();
		pipeline->loadUniform("color", color->getR(), color->getG(), color->getB());
		mesh->render();
		break;
	case CUBE:
		for (int i = 0;i<6;i++) {
			color = colors->getNextColor();
			pipeline->loadUniform("color", color->getR(), color->getG(), color->getB());
			mesh->render(i*6, 6);
		}
	}
}