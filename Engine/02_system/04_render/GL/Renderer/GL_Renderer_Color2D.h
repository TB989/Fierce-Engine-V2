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
class Entity2D;
class GL_Pipeline;

class GL_Renderer_Color2D:public GL_Renderer{

public:
	GL_Renderer_Color2D(GL_Pipeline* pipeline);

public:
	void addEntity(Entity2D* entity) { entities.push_back(entity); }
	void render();

private:
	GL_Pipeline* m_pipeline;
	std::vector<Entity2D*> entities;
};