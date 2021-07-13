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

class VertexAttribute{
public:
	static VertexAttribute* POS2;
	static VertexAttribute* POS3;
	static VertexAttribute* TEX;
	static VertexAttribute* NORMAL;
	static VertexAttribute* COLOR;
public:
	VertexAttribute(std::string name,GLuint location,GLint size,GLenum type);

	std::string getName() { return m_name; }
	GLuint getLocation() { return m_location; }
	GLint getSize() { return m_size; }
	GLenum getType() { return m_type; }
private:
	std::string m_name;
	GLuint m_location;
	GLint m_size;
	GLenum m_type;
};