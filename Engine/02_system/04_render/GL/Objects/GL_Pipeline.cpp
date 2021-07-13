#include "GL_Pipeline.h"

#include "02_system/01_logging/Logger.h"
#include "02_system/04_render/GL/GL_Shader.h"
#include "02_system/04_render/GL/VertexAttribute.h"
#include "04_math/02_matrix/Matrix.h"

GL_Pipeline::GL_Pipeline(std::string name,GL_Shader* shader1,GL_Shader* shader2){
	m_name = name;
	id = glCreateProgram();

	//Attach shaders
	shaderList.push_back(shader1);
	glAttachShader(id, shader1->getId());
	shaderList.push_back(shader2);
	glAttachShader(id, shader2->getId());
}

GL_Pipeline::~GL_Pipeline(){
	glUseProgram(0);
	for (int i = 0;i<shaderList.size();i++) {
		glDetachShader(id, shaderList[i]->getId());
	}
	glDeleteProgram(id);
}

void GL_Pipeline::create(){
	//Set vertex attributes
	for (VertexAttribute* attrib:vertexAttributes) {
		glBindAttribLocation(id, attrib->getLocation(), attrib->getName().c_str());
	}

	//Link program
	glLinkProgram(id);

	GLint Result = GL_FALSE;

	//Check linking
	glGetProgramiv(id, GL_LINK_STATUS, &Result);
	if (Result == GL_FALSE) {
		int InfoLogLength;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(id, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		Loggers::GL->error("Shader program linking failed for program %s:\n%s\n", m_name.c_str(), &ProgramErrorMessage[0]);
	}

	//Validate program
	glValidateProgram(id);

	//Check validation
	glGetProgramiv(id, GL_VALIDATE_STATUS, &Result);
	if (Result == GL_FALSE) {
		int InfoLogLength;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(id, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		Loggers::GL->error("Shader program validation failed for program %s:\n%s\n", m_name.c_str(), &ProgramErrorMessage[0]);
	}

	//Get uniform locations
	for (UniformLocation* loc : uniformLocations) {
		GLint location = glGetUniformLocation(id, loc->name.c_str());
		if (location == -1) {
			Loggers::GL->warn("Uniform location %s is not found in shader.", loc->name.c_str());
		}
		else {
			loc->location = location;
		}
	}
}

void GL_Pipeline::bind(){
	glUseProgram(id);
}

void GL_Pipeline::unbind(){
	glUseProgram(0);
}

void GL_Pipeline::addUniformLocation(std::string name){
	UniformLocation* loc = new UniformLocation();
	loc->name = name;
	loc->location = -1;
	uniformLocations.push_back(loc);
}

void GL_Pipeline::loadUniform(std::string name, float v1) {
	GLint load = -1;
	for (const UniformLocation* loc : uniformLocations) {
		if (loc->name.compare(name) == 0) {
			load = loc->location;
			glUniform1f(load, v1);
			return;
		}
	}

	Loggers::GL->warn("Uniform location %s is not found in shader.", name.c_str());
}

void GL_Pipeline::loadUniform(std::string name, float v1,float v2) {
	GLint load = -1;
	for (const UniformLocation* loc : uniformLocations) {
		if (loc->name.compare(name) == 0) {
			load = loc->location;
			glUniform2f(load, v1,v2);
			return;
		}
	}

	Loggers::GL->warn("Uniform location %s is not found in shader.", name.c_str());
}

void GL_Pipeline::loadUniform(std::string name, float v1, float v2,float v3) {
	GLint load = -1;
	for (const UniformLocation* loc : uniformLocations) {
		if (loc->name.compare(name) == 0) {
			load = loc->location;
			glUniform3f(load, v1, v2,v3);
			return;
		}
	}

	Loggers::GL->warn("Uniform location %s is not found in shader.", name.c_str());
}

void GL_Pipeline::loadUniform(std::string name, float v1, float v2, float v3,float v4) {
	GLint load = -1;
	for (const UniformLocation* loc : uniformLocations) {
		if (loc->name.compare(name) == 0) {
			load = loc->location;
			glUniform4f(load, v1, v2, v3,v4);
			return;
		}
	}

	Loggers::GL->warn("Uniform location %s is not found in shader.", name.c_str());
}

void GL_Pipeline::loadUniform(std::string name, Mat4* matrix){
	GLint load = -1;
	for (const UniformLocation* loc : uniformLocations) {
		if (loc->name.compare(name) == 0) {
			load = loc->location;
			glUniformMatrix4fv(load, 1, GL_TRUE, matrix->get());
			return;
		}
	}

	Loggers::GL->warn("Uniform location %s is not found in shader.", name.c_str());
}

void GL_Pipeline::addVertexAttribute(VertexAttribute* attribute){
	vertexAttributes.push_back(attribute);
}