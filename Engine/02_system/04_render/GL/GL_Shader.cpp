#include "GL_Shader.h"

#include "02_system/01_logging/Logger.h"

#include <fstream>

const std::string GL_Shader::SHADER_LIBRARY = "C:/Users/Tobias/Desktop/FierceEngine/Engine/xx_ressources/shaders/openGL/";

GL_Shader::GL_Shader(std::string path){
	type = getType(path);
	name = split(path, '.')[0];
	id = glCreateShader(type);

	//Load source code
	std::string source = readSourceCode(path);
	char const* sourceCode = source.c_str();
	glShaderSource(id, 1, &sourceCode, NULL);

	//Compile shader
	glCompileShader(id);

	//Check compile
	GLint Result = GL_FALSE;
	glGetShaderiv(id, GL_COMPILE_STATUS, &Result);
	if (Result == GL_FALSE) {
		int InfoLogLength;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(id, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		Loggers::GL->error("Shader compilation failed for shader %s:\n%s\n", path.c_str() , &VertexShaderErrorMessage[0]);
	}
}

GL_Shader::~GL_Shader(){
	glDeleteShader(id);
}

GLenum GL_Shader::getType(std::string path){
	if (endsWith(path, ".vs")) {
		return GL_VERTEX_SHADER;
	}
	else if (endsWith(path, ".fs")) {
		return GL_FRAGMENT_SHADER;
	}
	else if (endsWith(path, ".gs")) {
		return GL_GEOMETRY_SHADER;
	}
	else if (endsWith(path, ".tcs")) {
		return GL_TESS_CONTROL_SHADER;
	}
	else if (endsWith(path, ".tes")) {
		return GL_TESS_EVALUATION_SHADER;
	}
	else {
		Loggers::GL->error("Shader %s is not a valid shader file.", path.c_str());
		return -1;
	}
}

std::string GL_Shader::readSourceCode(std::string path){
	std::string code;
	std::ifstream stream(SHADER_LIBRARY + path, std::ios::in);

	if (stream.is_open()) {
		std::stringstream sstr;
		sstr << stream.rdbuf();
		code = sstr.str();
		stream.close();
	}
	else {
		Loggers::GL->error("Unable to read shader %s",path.c_str());
	}

	return code;
}