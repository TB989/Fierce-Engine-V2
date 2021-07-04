#include "VK_Pipeline.h"

#include "01_core/errorHandling/Exceptions.h"
#include <fstream>

VK_Pipeline::VK_Pipeline(VK_Device* device){
    m_device = device->getDevice();

    loadShaders();
    createShaderModules();
    createShaderStages();
    createVertexInput();
    createInputAssembly();
    createViewportScissor(device);
    createRasterizer();
    createMultisampling();
    createColorBlending();
    createPipeline();
}

VK_Pipeline::~VK_Pipeline(){
    vkDestroyPipelineLayout(m_device, pipelineLayout, nullptr);
    vkDestroyShaderModule(m_device, shaderModuleVert, nullptr);
    vkDestroyShaderModule(m_device, shaderModuleFrag, nullptr);
}

void VK_Pipeline::loadShaders(){
    std::ifstream file1("C:/Users/Tobias/Desktop/FierceEngine/Engine/xx_ressources/shaders/vulkan/firstShader_vert.spv", std::ios::ate | std::ios::binary);

    if (!file1.is_open()) {
        throw std::runtime_error("Failed to open file!");
    }

    size_t fileSize1 = (size_t)file1.tellg();
    bufferVert.resize(fileSize1);
    file1.seekg(0);
    file1.read(bufferVert.data(), fileSize1);

    file1.close();

    std::ifstream file2("C:/Users/Tobias/Desktop/FierceEngine/Engine/xx_ressources/shaders/vulkan/firstShader_frag.spv", std::ios::ate | std::ios::binary);

    if (!file2.is_open()) {
        throw std::runtime_error("Failed to open file!");
    }

    size_t fileSize2 = (size_t)file2.tellg();
    bufferFrag.resize(fileSize2);
    file2.seekg(0);
    file2.read(bufferFrag.data(), fileSize2);

    file2.close();
}

void VK_Pipeline::createShaderModules(){
    VkShaderModuleCreateInfo createInfo1{};
    createInfo1.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo1.pNext = nullptr;
    createInfo1.flags = 0;
    createInfo1.codeSize = bufferVert.size();
    createInfo1.pCode = reinterpret_cast<const uint32_t*>(bufferVert.data());

    CHECK_VK(vkCreateShaderModule(m_device, &createInfo1, nullptr, &shaderModuleVert), "Failed to create shader module.");

    VkShaderModuleCreateInfo createInfo2{};
    createInfo2.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo2.pNext = nullptr;
    createInfo2.flags = 0;
    createInfo2.codeSize = bufferFrag.size();
    createInfo2.pCode = reinterpret_cast<const uint32_t*>(bufferFrag.data());

    CHECK_VK(vkCreateShaderModule(m_device, &createInfo2, nullptr, &shaderModuleFrag), "Failed to create shader module.");
}

void VK_Pipeline::createShaderStages(){
    vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertShaderStageInfo.pNext = nullptr;
    vertShaderStageInfo.flags = 0;
    vertShaderStageInfo.pSpecializationInfo = nullptr;
    vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertShaderStageInfo.module = shaderModuleVert;
    vertShaderStageInfo.pName = "main";

    fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragShaderStageInfo.pNext = nullptr;
    fragShaderStageInfo.flags = 0;
    fragShaderStageInfo.pSpecializationInfo = nullptr;
    fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragShaderStageInfo.module = shaderModuleFrag;
    fragShaderStageInfo.pName = "main";

    shaderStages[0] = vertShaderStageInfo;
    shaderStages[1] = fragShaderStageInfo;
}

void VK_Pipeline::createVertexInput(){
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo.pNext = nullptr;
    vertexInputInfo.flags = 0;
    vertexInputInfo.vertexBindingDescriptionCount = 0;
    vertexInputInfo.pVertexBindingDescriptions = nullptr; // Optional
    vertexInputInfo.vertexAttributeDescriptionCount = 0;
    vertexInputInfo.pVertexAttributeDescriptions = nullptr; // Optional
}

void VK_Pipeline::createInputAssembly() {
    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.pNext = nullptr;
    inputAssembly.flags = 0;
    inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssembly.primitiveRestartEnable = VK_FALSE;
}

void VK_Pipeline::createViewportScissor(VK_Device* device){
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float)device->getExtent().width;
    viewport.height = (float)device->getExtent().height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    scissor.offset = { 0, 0 };
    scissor.extent = device->getExtent();

    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.pNext = nullptr;
    viewportState.flags = 0;
    viewportState.viewportCount = 1;
    viewportState.pViewports = &viewport;
    viewportState.scissorCount = 1;
    viewportState.pScissors = &scissor;
}

void VK_Pipeline::createRasterizer(){
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.pNext = nullptr;
    rasterizer.flags = 0;
    rasterizer.depthClampEnable = VK_FALSE;
    rasterizer.rasterizerDiscardEnable = VK_FALSE;
    rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizer.lineWidth = 1.0f;
    rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
    rasterizer.depthBiasEnable = VK_FALSE;
    rasterizer.depthBiasConstantFactor = 0.0f; // Optional
    rasterizer.depthBiasClamp = 0.0f; // Optional
    rasterizer.depthBiasSlopeFactor = 0.0f; // Optional
}

void VK_Pipeline::createMultisampling(){
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.pNext = nullptr;
    multisampling.flags = 0;
    multisampling.sampleShadingEnable = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    multisampling.minSampleShading = 1.0f; // Optional
    multisampling.pSampleMask = nullptr; // Optional
    multisampling.alphaToCoverageEnable = VK_FALSE; // Optional
    multisampling.alphaToOneEnable = VK_FALSE; // Optional
}

void VK_Pipeline::createColorBlending(){
    colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    colorBlendAttachment.blendEnable = VK_FALSE;
    colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
    colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
    colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD; // Optional
    colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
    colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
    colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD; // Optional

    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.pNext = nullptr;
    colorBlending.flags = 0;
    colorBlending.logicOpEnable = VK_FALSE;
    colorBlending.logicOp = VK_LOGIC_OP_COPY; // Optional
    colorBlending.attachmentCount = 1;
    colorBlending.pAttachments = &colorBlendAttachment;
    colorBlending.blendConstants[0] = 0.0f; // Optional
    colorBlending.blendConstants[1] = 0.0f; // Optional
    colorBlending.blendConstants[2] = 0.0f; // Optional
    colorBlending.blendConstants[3] = 0.0f; // Optional
}

void VK_Pipeline::createPipeline(){
    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.pNext = nullptr;
    pipelineLayoutInfo.flags = 0;
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0; // Optional
    pipelineLayoutInfo.pSetLayouts = nullptr; // Optional
    pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
    pipelineLayoutInfo.pPushConstantRanges = nullptr; // Optional

    CHECK_VK(vkCreatePipelineLayout(m_device, &pipelineLayoutInfo, nullptr, &pipelineLayout),"Failed to create pipeline layout.");
}