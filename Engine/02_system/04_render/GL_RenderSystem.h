#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "01_core/EngineSettings.h"
#include "02_system/04_render/RenderType.h"

/* SystemIncludes*/
#include <vector>
#include <unordered_map>

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/
class Core;
class GL_Context;
class GL_Abstract_Renderer_2D;
class GL_Abstract_Renderer_3D;
class Mat4;
class Entity2D;
class Entity3D;

class GL_RenderSystem{
public:
	GL_RenderSystem(Core* app, EngineSettings* settings,Entity3D* camera);
	~GL_RenderSystem();

	void addEntity(Entity2D* entity);
	void addEntity(Entity3D* entity);
	void render();

private:
	void addRenderers();

private:
	GL_Context* context = nullptr;

	std::unordered_map<RenderType, GL_Abstract_Renderer_2D*> renderers2D;
	std::unordered_map<RenderType, GL_Abstract_Renderer_3D*> renderers3D;

	Entity3D* m_camera;
};