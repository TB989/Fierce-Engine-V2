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

class GL_Shader;
class GL_Pipeline;
class GL_Renderer;
class Entity3D;
struct EngineSettings;

class GL_RenderSystem:public Abstract_RenderSystem{
public:
	GL_RenderSystem(Core* app, EngineSettings* settings, Entity3D* camera);
	~GL_RenderSystem();

	void loadShaders() override;
	void loadPipelines() override;
	void loadRenderers();

	void render();

private:
	std::unordered_map<std::string, GL_Shader*> shaders;
	std::unordered_map<std::string, GL_Pipeline*> pipelines;
	std::unordered_map<std::string, GL_Renderer*> renderers2D;
	std::unordered_map<std::string, GL_Renderer*> renderers3D;

	GL_Context* context = nullptr;
	Entity3D* m_camera;
};