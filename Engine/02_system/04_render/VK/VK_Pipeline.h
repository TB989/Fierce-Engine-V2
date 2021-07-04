#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "02_system/04_render/VK/VK_Device.h"


/* SystemIncludes*/
#include "vulkan/vulkan.h"
#include <vector>

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/

class VK_Pipeline{
public:
	VK_Pipeline(VK_Device* device);
	~VK_Pipeline();

private:
	VkDevice m_device;

	std::vector<char> bufferVert;
	std::vector<char> bufferFrag;
	VkShaderModule shaderModuleVert;
	VkShaderModule shaderModuleFrag;
	VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
	VkPipelineShaderStageCreateInfo fragShaderStageInfo{};

	VkPipelineShaderStageCreateInfo shaderStages[2];
	VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
	VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
	VkViewport viewport{};
	VkRect2D scissor{};
	VkPipelineViewportStateCreateInfo viewportState{};
	VkPipelineRasterizationStateCreateInfo rasterizer{};
	VkPipelineMultisampleStateCreateInfo multisampling{};
	VkPipelineColorBlendAttachmentState colorBlendAttachment{};
	VkPipelineColorBlendStateCreateInfo colorBlending{};


	VkPipelineLayout pipelineLayout;

private:
	void loadShaders();
	void createShaderModules();
	void createShaderStages();
	void createVertexInput();
	void createInputAssembly();
	void createViewportScissor(VK_Device* device);
	void createRasterizer();
	void createMultisampling();
	void createColorBlending();
	void createPipeline();
};