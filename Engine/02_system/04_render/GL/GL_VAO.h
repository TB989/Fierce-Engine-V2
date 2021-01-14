#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "Fierce_GL.h"


/* SystemIncludes*/
#include <vector>

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/
class GL_VBO;
class VertexAttribute;

class GL_VAO {
public:
	GL_VAO(GL_VBO* vertexBuffer);
	GL_VAO(GL_VBO* vertexBuffer,GL_VBO* indexBuffer);
	~GL_VAO();
	void bind();
	void unbind();

	void addVertexAttribute(VertexAttribute* attribute);
	void draw();
private:
	GLuint m_id;
	GL_VBO* m_vertexBuffer=nullptr;
	GL_VBO* m_indexBuffer = nullptr;
	std::vector<VertexAttribute*> vertexAttributes;
	int numElements;
};