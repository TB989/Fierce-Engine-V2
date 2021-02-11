#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "GL_Abstract_Renderer.h"
#include "05_ECS/Entity.h"

/* SystemIncludes*/
#include <vector>

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/

class GL_Abstract_Renderer_2D:public GL_Abstract_Renderer{
protected:
	std::vector<Entity2D*> entities;

public:
	void addEntity(Entity2D* entity) { entities.push_back(entity); }
	void render();

protected:
	virtual void prepareRendering();
	virtual void prepareEntity(Entity2D* entity);
	virtual void renderEntity(Entity2D* entity);
	virtual void finishRendering();
};
