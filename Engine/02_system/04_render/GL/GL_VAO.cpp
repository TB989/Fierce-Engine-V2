#include "GL_VAO.h"

#include "GL_VBO.h"

GL_VAO::GL_VAO(GL_VBO* vertexBuffer){
	glGenVertexArrays(1, &m_id);
	m_vertexBuffer = vertexBuffer;
}

GL_VAO::~GL_VAO(){
	glDeleteVertexArrays(1, &m_id);
}

void GL_VAO::bind(){
	glBindVertexArray(m_id);
}

void GL_VAO::unbind(){
	glBindVertexArray(0);
}

void GL_VAO::vertexAttribPointer(GLuint index,GLint size,GLenum type){
	glBindVertexArray(m_id);
	m_vertexBuffer->bind();
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index,size,type,GL_FALSE,0,(void*)0);
	glBindVertexArray(0);
	m_vertexBuffer->unbind();
}

void GL_VAO::draw(){
	glDrawArrays(GL_TRIANGLES, 0, 3);
}