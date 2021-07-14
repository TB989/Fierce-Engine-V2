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

class GL_VBO {
public:
	GL_VBO(GLenum type);
	~GL_VBO();
	void bind();
	void unbind();

	GLsizeiptr getSize() { return m_size; }

	void loadData(GLsizeiptr size, const void* data, GLenum usage);
private:
	GLenum m_type;
	GLuint m_id;
	GLsizeiptr m_size;
};