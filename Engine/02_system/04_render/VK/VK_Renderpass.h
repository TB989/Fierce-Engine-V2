#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "02_system/04_render/VK/VK_Device.h"

/* SystemIncludes*/
#include "vulkan/vulkan.h"

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/

class VK_Renderpass{
public:
	VK_Renderpass(VK_Device* device);
	~VK_Renderpass();

	VkRenderPass getRenderpass() { return renderPass; }

private:
	VkDevice m_device;
	VkRenderPass renderPass;
};