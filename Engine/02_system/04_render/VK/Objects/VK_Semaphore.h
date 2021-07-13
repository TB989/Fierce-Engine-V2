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

class VK_Semaphore{
public:
	VK_Semaphore(VK_Device* device);
	~VK_Semaphore();

	VkSemaphore getSemaphore() { return semaphore; }

private:
	VK_Device* m_device;
	VkSemaphore semaphore;
};