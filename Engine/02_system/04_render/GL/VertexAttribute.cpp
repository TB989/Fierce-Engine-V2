#include "VertexAttribute.h"

VertexAttribute::VertexAttribute(std::string name, GLuint location, GLint size, GLenum type){
	m_name = name;
	m_location = location;
	m_size = size;
	m_type = type;
}

VertexAttribute* VertexAttribute::POS2 = new VertexAttribute("position", 0, 2, GL_FLOAT);
VertexAttribute* VertexAttribute::POS3 = new VertexAttribute("position", 0, 3, GL_FLOAT);
VertexAttribute* VertexAttribute::TEX = new VertexAttribute("textureCoordinate", 1, 2, GL_FLOAT);
VertexAttribute* VertexAttribute::NORMAL = new VertexAttribute("normal", 2, 3, GL_FLOAT);
VertexAttribute* VertexAttribute::COLOR = new VertexAttribute("color", 3, 3, GL_FLOAT);