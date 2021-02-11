#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "GL_Abstract_Renderer_3D.h"

/* SystemIncludes*/

/* Forward declarations:
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/

class GL_Renderer_Geometry3D :public GL_Abstract_Renderer_3D {
public:
	GL_Renderer_Geometry3D();

public:
	void loadShaders() override;
	void createPipeline() override;
};