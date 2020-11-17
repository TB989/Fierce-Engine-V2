#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "Fierce_GL.h"
#include "99_utils/FierceStrings.h"

/* SystemIncludes*/

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/

class GL_Shader{
public:
	GL_Shader(std::string path);
	~GL_Shader();

	GLuint getId() { return id; };
private:
	GLenum getType(std::string path);
	std::string readSourceCode(std::string path);

private:
	static const std::string SHADER_LIBRARY;

	std::string name="";
	GLuint id=-1;
	GLenum type=-1;
};