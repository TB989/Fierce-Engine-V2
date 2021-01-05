#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "02_system/04_render/GL/GL_Shader.h"

/* SystemIncludes*/

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/

class GL_Shader_Color : public GL_Shader{
public:
	GL_Shader_Color(std::string path) :GL_Shader(path) {};
};