#include "VK_Framebuffers.h"

#include "01_core/errorHandling/Exceptions.h"

VK_Framebuffers::VK_Framebuffers(VK_Device* device, VK_Presentation* presentation, VK_Renderpass* renderpass){
    m_device = device->getDevice();
	framebuffers.resize(presentation->getNumImages());

    for (size_t i = 0; i < framebuffers.size(); i++) {
        VkImageView attachments[] = {
            presentation->getImageView(i)
        };

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.pNext = nullptr;
        framebufferInfo.flags = 0;
        framebufferInfo.renderPass = renderpass->getRenderpass();
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = attachments;
        framebufferInfo.width = device->getExtent().width;
        framebufferInfo.height = device->getExtent().height;
        framebufferInfo.layers = 1;

        CHECK_VK(vkCreateFramebuffer(m_device, &framebufferInfo, nullptr, &framebuffers[i]),"Failed to create framebuffer.");
    }
}

VK_Framebuffers::~VK_Framebuffers(){
    for (auto framebuffer : framebuffers) {
        vkDestroyFramebuffer(m_device, framebuffer, nullptr);
    }
}