#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "02_system/04_render/VK/VK_Device.h"
#include "02_system/04_render/VK/VK_Renderpass.h"

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
class VK_Device;
class VK_Shader;
class VK_Renderpass;

class VK_Pipeline{
public:
	VK_Pipeline(VK_Device* device,VK_Shader* vertexShader,VK_Shader* fragmentShader,VK_Renderpass* renderpass);
	~VK_Pipeline();

	VkPipeline getPipeline() { return graphicsPipeline; }

private:
	VkDevice m_device;

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
	VkPipeline graphicsPipeline;

private:
	void createShaderStages(VK_Shader* vertexShader, VK_Shader* fragmentShader);
	void createVertexInput();
	void createInputAssembly();
	void createViewportScissor(VK_Device* device);
	void createRasterizer();
	void createMultisampling();
	void createColorBlending();
	void createPipeline(VkRenderPass renderpass);
};