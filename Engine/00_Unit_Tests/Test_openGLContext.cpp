#include "UnitTests.h"

#include <fstream>

#include "02_system/01_logging/Logger.h"
#include "02_system/02_event/EventSystem.h"
#include "02_system/03_window/WindowSystem.h"
#include "02_system/04_render/GL/GL_Context.h"
#include "02_system/04_render/GL/Fierce_GL.h"
#include "03_io/parser/Parser.h"

GLuint vaoId;
GLuint vboId;

GLuint vsId;
GLuint fsId;
GLuint pId;

Test_openGLContext::Test_openGLContext() {
	eventSystem->addListener(this, &Test_openGLContext::onAppInit);
	eventSystem->addListener(this, &Test_openGLContext::onAppUpdate);
	eventSystem->addListener(this, &Test_openGLContext::onAppCleanUp);

	eventSystem->addListener(this, &Test_openGLContext::onWindowResize);
}

void Test_openGLContext::onAppInit(AppInitEvent* event) {
	std::map<std::string, std::string> settings = Parser::parsePropertiesFile("C:/Users/Tobias/Desktop/GameEngine/Engine/Engine.ini");
	m_settings.parse(settings);

	context = new GL_Context(this);

	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	// An array of 3 vectors which represents 3 vertices
	static const GLfloat g_vertex_buffer_data[] = {
	   -1.0f, -1.0f, 0.0f,
	   1.0f, -1.0f, 0.0f,
	   0.0f,  1.0f, 0.0f,
	};

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vboId);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	vsId = glCreateShader(GL_VERTEX_SHADER);
	fsId = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vsCode;
	std::ifstream vsStream("C:/Users/Tobias/Desktop/GameEngine/Engine/xx_ressources/shaders/openGL/MyFirstShader.vert", std::ios::in);
	if (vsStream.is_open()) {
		std::stringstream sstr;
		sstr << vsStream.rdbuf();
		vsCode = sstr.str();
		vsStream.close();
	}
	else {
		Loggers::GL->error("Unable to read vertex shader.");
	}

	std::string fsCode;
	std::ifstream fsStream("C:/Users/Tobias/Desktop/GameEngine/Engine/xx_ressources/shaders/openGL/MyFirstShader.frag", std::ios::in);
	if (fsStream.is_open()) {
		std::stringstream sstr;
		sstr << fsStream.rdbuf();
		fsCode = sstr.str();
		fsStream.close();
	}
	else {
		Loggers::GL->error("Unable to read fragment shader.");
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	char const* VertexSourcePointer = vsCode.c_str();
	glShaderSource(vsId, 1, &VertexSourcePointer, NULL);
	glCompileShader(vsId);

	// Check Vertex Shader
	glGetShaderiv(vsId, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(vsId, GL_INFO_LOG_LENGTH, &InfoLogLength);

	if (Result==GL_FALSE) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(vsId, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		Loggers::GL->error("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	char const* FragmentSourcePointer = fsCode.c_str();
	glShaderSource(fsId, 1, &FragmentSourcePointer, NULL);
	glCompileShader(fsId);

	// Check Fragment Shader
	glGetShaderiv(fsId, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fsId, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (Result==GL_FALSE) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(fsId, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		Loggers::GL->error("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	pId = glCreateProgram();
	glAttachShader(pId, vsId);
	glAttachShader(pId, fsId);
	glLinkProgram(pId);

	// Check the program
	glGetProgramiv(pId, GL_LINK_STATUS, &Result);
	glGetProgramiv(pId, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (Result==GL_FALSE) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(pId, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		Loggers::GL->error("%s\n", &ProgramErrorMessage[0]);
	}

	glValidateProgram(pId);
	glGetProgramiv(pId, GL_VALIDATE_STATUS, &Result);
	glGetProgramiv(pId, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (Result == GL_FALSE) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(pId, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		Loggers::GL->error("%s\n", &ProgramErrorMessage[0]);
	}
}

void Test_openGLContext::onAppUpdate(AppUpdateEvent* event) {
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,vboId);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	glUseProgram(pId);
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);

	context->swapBuffers();
}

void Test_openGLContext::onAppCleanUp(AppCleanUpEvent* event) {
	delete context;
}

void Test_openGLContext::onWindowResize(WindowResizeEvent* event) {
	Loggers::CORE->info("Resize to [%ix%i]", event->m_width, event->m_height);
}