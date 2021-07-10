#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "02_system/04_render/VK/VK_Device.h"
#include "02_system/04_render/VK/VK_Presentation.h"
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

class VK_Framebuffers{
public:
	VK_Framebuffers(VK_Device* device,VK_Presentation* presentation,VK_Renderpass* renderpass);
	~VK_Framebuffers();

	VkFramebuffer getFramebuffer(int index) { return framebuffers[index]; }

private:
	VkDevice m_device;
	std::vector<VkFramebuffer> framebuffers;
};