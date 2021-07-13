#include "VK_Shader.h"

#include "01_core/errorHandling/Exceptions.h"
#include "02_system/01_logging/Logger.h"
#include "02_system/04_render/VK/VK_Device.h"

#include <fstream>

const std::string VK_Shader::SHADER_LIBRARY = "C:/Users/Tobias/Desktop/FierceEngine/Engine/xx_ressources/shaders/vulkan/";

VK_Shader::VK_Shader(VK_Device* device,std::string path){
	m_device = device->getDevice();

	type = getType(path);
	readSourceCode(path);
	createShader(path);
}

VK_Shader::~VK_Shader(){
	vkDestroyShaderModule(m_device, shaderModule, nullptr);
}

void VK_Shader::fillInShaderStageInfo(VkPipelineShaderStageCreateInfo createInfo){
	createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.pSpecializationInfo = nullptr;
	switch (type) {
	case VERTEX_SHADER:
		createInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
		break;
	case FRAGMENT_SHADER:
		createInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		break;
	}
	createInfo.module = shaderModule;
	createInfo.pName = "main";
}

ShaderType VK_Shader::getType(std::string path) {
	if (contains(path, "vert")) {
		return ShaderType::VERTEX_SHADER;
	}
	else if (contains(path, "frag")) {
		return ShaderType::FRAGMENT_SHADER;
	}
	else {
		Loggers::VK->error("Shader %s is not a valid shader file.", path.c_str());
		return ShaderType::UNKNOWN;
	}
}

void VK_Shader::readSourceCode(std::string path){
	std::ifstream stream(SHADER_LIBRARY + path, std::ios::ate | std::ios::binary);

	if (stream.is_open()) {
		size_t fileSize = (size_t)stream.tellg();
		sourceCode.resize(fileSize);
		stream.seekg(0);
		stream.read(sourceCode.data(), fileSize);
		stream.close();
	}
	else {
		Loggers::VK->error("Unable to read shader %s.", path.c_str());
	}
}

void VK_Shader::createShader(std::string path){
	VkShaderModuleCreateInfo createInfo1{};
	createInfo1.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo1.pNext = nullptr;
	createInfo1.flags = 0;
	createInfo1.codeSize = sourceCode.size();
	createInfo1.pCode = reinterpret_cast<const uint32_t*>(sourceCode.data());

	CHECK_VK(vkCreateShaderModule(m_device, &createInfo1, nullptr, &shaderModule), "Failed to create shader module.");
}