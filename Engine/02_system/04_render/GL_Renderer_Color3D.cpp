#include "GL_Renderer_Color3D.h"

#include "02_system/04_render/GL/GL_Shader.h"
#include "02_system/04_render/GL/GL_Pipeline.h"
#include "02_system/04_render/GL/VertexAttribute.h"

GL_Renderer_Color3D::GL_Renderer_Color3D(){
	loadShaders();
	createPipeline();
}

void GL_Renderer_Color3D::loadShaders(){
	vertexShader = new GL_Shader("Shader_Color3D.vs");
	fragmentShader = new GL_Shader("Shader_Color.fs");
}

void GL_Renderer_Color3D::createPipeline(){
	pipeline = new GL_Pipeline("Color_3D", vertexShader, fragmentShader);
	pipeline->addVertexAttribute(VertexAttribute::POS3);
	pipeline->addUniformLocation("projectionMatrix");
	pipeline->addUniformLocation("viewMatrix");
	pipeline->addUniformLocation("modelMatrix");
	pipeline->addUniformLocation("color");
	pipeline->create();
}