#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "02_system/04_render/GL/GL_Pipeline.h"
#include "02_system/04_render/GL/GL_Shader.h"
#include "04_math/02_matrix/Matrix.h"

/* SystemIncludes*/
#include <vector>

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/

class GL_Abstract_Renderer{
public:
	~GL_Abstract_Renderer();

	GL_Pipeline* getPipeline();

protected:
	GL_Shader* vertexShader;
	GL_Shader* fragmentShader;
	GL_Pipeline* pipeline;

public:
	virtual void loadShaders()=0;
	virtual void createPipeline()=0;
};