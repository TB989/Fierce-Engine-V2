#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "GL_Renderer.h"

/* SystemIncludes*/
#include <vector>

/* Forward declarations:
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/
class Entity3D;
class GL_Pipeline;

class GL_Renderer_Geometry3D :public GL_Renderer {
public:
	GL_Renderer_Geometry3D(GL_Pipeline* pipeline);

public:
	void addEntity(Entity3D* entity) { entities.push_back(entity); }
	void render();

private:
	GL_Pipeline* m_pipeline;
	std::vector<Entity3D*> entities;

	void renderEntity(Entity3D* entity);
};