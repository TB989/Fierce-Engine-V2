#include "GL_Abstract_Renderer.h"

#include "02_system/01_logging/Logger.h"

GL_Abstract_Renderer::~GL_Abstract_Renderer(){
	delete pipeline;
	delete vertexShader;
	delete fragmentShader;
}

GL_Pipeline* GL_Abstract_Renderer::getPipeline(){
	return pipeline;
}