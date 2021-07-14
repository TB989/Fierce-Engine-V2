#include "GL_MeshLoader.h"

#include "02_system/04_render/02_GL/01_Objects/Fierce_GL.h"
#include "02_system/04_render/02_GL/01_Objects/GL_VAO.h"
#include "02_system/04_render/02_GL/01_Objects/GL_VBO.h"

GL_VAO* GL_MeshLoader::loadMesh(std::vector<float>& vertices, std::vector<unsigned int>& indices, VertexAttribute* attribute1){
	/**GL_VBO* vbo = new GL_VBO(GL_ARRAY_BUFFER);
	vbo->loadData(sizeof(GLfloat) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	GL_VBO* vboi = new GL_VBO(GL_ELEMENT_ARRAY_BUFFER);
	vboi->loadData(sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);

	GL_VAO* vao = new GL_VAO(vbo, vboi);
	vao->addVertexAttribute(attribute1);

	return vao;*/

	return nullptr;
}

GL_VAO* GL_MeshLoader::loadMesh(std::vector<float>& vertices, std::vector<unsigned int>& indices, VertexAttribute* attribute1, VertexAttribute* attribute2) {
	/**GL_VBO* vbo = new GL_VBO(GL_ARRAY_BUFFER);
	vbo->loadData(sizeof(GLfloat) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	GL_VBO* vboi = new GL_VBO(GL_ELEMENT_ARRAY_BUFFER);
	vboi->loadData(sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);

	GL_VAO* vao = new GL_VAO(vbo, vboi);
	vao->addVertexAttribute(attribute1);
	vao->addVertexAttribute(attribute2);

	return vao;*/

	return nullptr;
}

GL_VAO* GL_MeshLoader::loadMesh(std::vector<float>& vertices, std::vector<unsigned int>& indices, VertexAttribute* attribute1, VertexAttribute* attribute2, VertexAttribute* attribute3) {
	/**GL_VBO* vbo = new GL_VBO(GL_ARRAY_BUFFER);
	vbo->loadData(sizeof(GLfloat) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	GL_VBO* vboi = new GL_VBO(GL_ELEMENT_ARRAY_BUFFER);
	vboi->loadData(sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);

	GL_VAO* vao = new GL_VAO(vbo, vboi);
	vao->addVertexAttribute(attribute1);
	vao->addVertexAttribute(attribute2);
	vao->addVertexAttribute(attribute3);

	return vao;*/

	return nullptr;
}