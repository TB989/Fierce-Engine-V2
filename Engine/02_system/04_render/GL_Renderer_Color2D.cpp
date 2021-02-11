#include "GL_Renderer_Color2D.h"

#include "02_system/04_render/GL/GL_Shader.h"
#include "02_system/04_render/GL/GL_Pipeline.h"
#include "02_system/04_render/GL/VertexAttribute.h"

#include "02_system/01_logging/Logger.h"

GL_Renderer_Color2D::GL_Renderer_Color2D() {
	loadShaders();
	createPipeline();
}

void GL_Renderer_Color2D::loadShaders(){
	vertexShader = new GL_Shader("Shader_Color2D.vs");
	fragmentShader = new GL_Shader("Shader_Color.fs");
}

void GL_Renderer_Color2D::createPipeline(){
	pipeline = new GL_Pipeline("Color_2D", vertexShader, fragmentShader);
	pipeline->addVertexAttribute(VertexAttribute::POS2);
	pipeline->addUniformLocation("projectionMatrix");
	pipeline->addUniformLocation("modelMatrix");
	pipeline->addUniformLocation("color");
	pipeline->create();
}

void GL_Renderer_Color2D::prepareEntity(Entity2D* entity) {
	GL_Abstract_Renderer_2D::prepareEntity(entity);

	ComponentMaterialColor* color = (ComponentMaterialColor*)(entity->getComponent(ComponentType::MATERIAL_COLOR));
	pipeline->loadUniform("color", color->getR(), color->getG(), color->getB());
}