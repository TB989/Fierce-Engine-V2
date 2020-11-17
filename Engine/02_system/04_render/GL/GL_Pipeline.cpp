#include "GL_Pipeline.h"

#include "02_system/01_logging/Logger.h"
#include "02_system/04_render/GL/GL_Shader.h"

GL_Pipeline::GL_Pipeline(std::string name,GL_Shader* shader1,GL_Shader* shader2){
	m_name = name;
	id = glCreateProgram();

	//Attach shaders
	shaderList.push_back(shader1);
	glAttachShader(id, shader1->getId());
	shaderList.push_back(shader2);
	glAttachShader(id, shader2->getId());

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
}

GL_Pipeline::~GL_Pipeline(){
	glUseProgram(0);
	for (int i = 0;i<shaderList.size();i++) {
		glDetachShader(id, shaderList[i]->getId());
	}
	glDeleteProgram(id);
}

void GL_Pipeline::bind(){
	glUseProgram(id);
}

void GL_Pipeline::unbind(){
	glUseProgram(0);
}