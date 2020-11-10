#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "Fierce_GL.h"


/* SystemIncludes*/

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/
class GL_VBO;

class GL_VAO {
public:
	GL_VAO(GL_VBO* vertexBuffer);
	~GL_VAO();
	void bind();
	void unbind();

	void vertexAttribPointer(GLuint index, GLint size, GLenum type);
private:
	GLuint m_id;
	GL_VBO* m_vertexBuffer=nullptr;
};