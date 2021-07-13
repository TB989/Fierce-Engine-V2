#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/

/* SystemIncludes*/
#include "vulkan/vulkan.h"

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/
class VK_Device;

class VK_Fence{
public:
	VK_Fence(VK_Device* device);
	~VK_Fence();

	VkFence getFence() { return fence; }

private:
	VK_Device* m_device;
	VkFence fence;
};