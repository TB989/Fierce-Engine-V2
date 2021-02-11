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

class GL_Abstract_Renderer_3D :public GL_Abstract_Renderer {
protected:
	std::vector<Entity3D*> entities;

public:
	void addEntity(Entity3D* entity) { entities.push_back(entity); }
	void render();

protected:
	virtual void prepareRendering();
	virtual void prepareEntity(Entity3D* entity);
	virtual void renderEntity(Entity3D* entity);
	virtual void finishRendering();
};