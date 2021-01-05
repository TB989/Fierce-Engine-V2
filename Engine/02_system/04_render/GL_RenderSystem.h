#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "01_core/EngineSettings.h"
#include "99_utils/FierceStrings.h"

/* SystemIncludes*/
#include <map>
#include <vector>

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/
class Core;
class GL_Context;
class GL_Shader;
class GL_Pipeline;
class Mat4;
class Entity2D;
class Entity3D;

class GL_RenderSystem{
public:
	GL_RenderSystem(Core* app, EngineSettings* settings);
	~GL_RenderSystem();

	void addEntity(Entity2D* entity);
	void addEntity(Entity3D* entity);
	void render();

private:
	void loadShaders();
	void loadPipelines();

private:
	GL_Context* context = nullptr;
	Mat4* orthographicProjectionMatrix;
	Mat4* perspectiveProjectionMatrix;
	std::map<std::string, GL_Shader*> shaders;
	std::map<std::string, GL_Pipeline*> pipelines;

	std::vector<Entity2D*> entities2D;
	std::vector<Entity3D*> entities3D;
};