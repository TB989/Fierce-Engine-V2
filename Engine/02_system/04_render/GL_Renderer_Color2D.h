#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "GL_Abstract_Renderer_2D.h"

/* SystemIncludes*/

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/

class GL_Renderer_Color2D:public GL_Abstract_Renderer_2D{
public:
	GL_Renderer_Color2D();

public:
	void loadShaders();
	void createPipeline();

	void prepareEntity(Entity2D* entity);
};