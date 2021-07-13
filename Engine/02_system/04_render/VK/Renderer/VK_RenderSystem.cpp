#include "VK_RenderSystem.h"

#include "02_system/04_render/VK/VK_Device.h"
#include "02_system/04_render/VK/VK_Shader.h"
#include "02_system/04_render/VK/VK_Pipeline.h"
#include "02_system/04_render/VK/VK_Renderpass.h"

VK_RenderSystem::VK_RenderSystem(VK_Device* device){
	m_device = device;

	loadRenderPasses();
	loadShaders();
	loadPipelines();
}

VK_RenderSystem::~VK_RenderSystem(){
	for (auto it = pipelines.begin(); it != pipelines.end(); it++) {
		delete it->second;
	}
	for (auto it = shaders.begin(); it != shaders.end(); it++) {
		delete it->second;
	}
	for (auto it = renderPasses.begin(); it != renderPasses.end(); it++) {
		delete it->second;
	}
}

void VK_RenderSystem::loadRenderPasses(){
	renderPasses["standard"] = new VK_Renderpass(m_device);
}

void VK_RenderSystem::loadShaders(){
	//Vertex shaders
	shaders["firstShader.vs"] = new VK_Shader(m_device,"firstShader_vert.spv");

	//Fragment shaders
	shaders["firstShader.fs"] = new VK_Shader(m_device,"firstShader_frag.spv");
}

void VK_RenderSystem::loadPipelines(){
	pipelines["first"] = new VK_Pipeline(m_device,shaders["firstShader.vs"], shaders["firstShader.fs"],renderPasses["standard"]);
}