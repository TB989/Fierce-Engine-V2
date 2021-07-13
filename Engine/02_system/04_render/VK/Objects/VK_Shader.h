#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "02_system/04_render/01_Abstract/ShaderType.h"

/* SystemIncludes*/
#include "vulkan/vulkan.h"
#include <vector>
#include "99_utils/FierceStrings.h"

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/
class VK_Device;

class VK_Shader{
public:
	VK_Shader(VK_Device* device,std::string path);
	~VK_Shader();

	VkShaderModule getId() { return shaderModule; }
	void fillInShaderStageInfo(VkPipelineShaderStageCreateInfo createInfo);

private:
	ShaderType getType(std::string path);
	void readSourceCode(std::string path);
	void createShader(std::string path);

private:
	static const std::string SHADER_LIBRARY;

	VkDevice m_device;

	ShaderType type;
	std::vector<char> sourceCode;
	VkShaderModule shaderModule;
};