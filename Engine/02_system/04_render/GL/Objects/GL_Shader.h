#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "Fierce_GL.h"
#include "02_system/04_render/01_Abstract/ShaderType.h"
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
	ShaderType getType(std::string path);
	void readSourceCode(std::string path);
	void createShader(std::string path);

private:
	static const std::string SHADER_LIBRARY;

	ShaderType type;
	std::string sourceCode;
	GLuint id = -1;
};