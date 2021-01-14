#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "Fierce_GL.h"
#include "99_utils/FierceStrings.h"

/* SystemIncludes*/
#include <vector>

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/
class GL_Shader;
class Mat4;
class VertexAttribute;

class GL_Pipeline{
public:
	GL_Pipeline(std::string name,GL_Shader* shader1,GL_Shader* shader2);
	~GL_Pipeline();

	void create();

	void bind();
	void unbind();

	void addUniformLocation(std::string name);
	void loadUniform(std::string location, Mat4* matrix);

	void addVertexAttribute(VertexAttribute* attribute);

private:
	struct UniformLocation {
		std::string name;
		GLint location;
	};

private:
	GLuint id;
	std::string m_name;
	std::vector<GL_Shader*> shaderList;

	std::vector<UniformLocation*> uniformLocations;
	std::vector<VertexAttribute*> vertexAttributes;
};