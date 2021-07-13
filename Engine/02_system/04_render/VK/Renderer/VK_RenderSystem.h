#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "02_system/04_render/01_Abstract/Abstract_RenderSystem.h"
#include "99_utils/FierceStrings.h"

/* SystemIncludes*/
#include<unordered_map>

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/

class VK_Device;
class VK_Shader;
class VK_Pipeline;
class VK_Renderpass;
class VK_Renderer;

class VK_RenderSystem :public Abstract_RenderSystem {
public:
	VK_RenderSystem(VK_Device* device);
	~VK_RenderSystem();

	void loadRenderPasses();
	void loadShaders() override;
	void loadPipelines() override;

private:
	VK_Device* m_device;

	std::unordered_map<std::string, VK_Renderpass*> renderPasses;
	std::unordered_map<std::string, VK_Shader*> shaders;
	std::unordered_map<std::string, VK_Pipeline*> pipelines;
	std::unordered_map<std::string, VK_Renderer*> renderers;
};