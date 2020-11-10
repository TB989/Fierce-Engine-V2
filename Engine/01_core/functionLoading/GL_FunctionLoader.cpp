#include "GL_FunctionLoader.h"

#include "02_system/01_logging/Logger.h"
#include "02_system/04_render/GL/Fierce_GL.h"

//**********Vertex arrays**************************
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray;

PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
//*************************************************

//**********Buffers********************************
PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLDELETEBUFFERSPROC glDeleteBuffers;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLBUFFERDATAPROC glBufferData;
//*************************************************

//**********Shaders********************************
PFNGLCREATESHADERPROC glCreateShader;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
//*************************************************

//**********Shaders Program************************
PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLVALIDATEPROGRAMPROC glValidateProgram;
PFNGLGETPROGRAMIVPROC glGetProgramiv;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
PFNGLDETACHSHADERPROC glDetachShader;
PFNGLDELETESHADERPROC glDeleteShader;
PFNGLUSEPROGRAMPROC glUseProgram;
//*************************************************

void* getGLFunctionPointer(const char* name) {
	void* p = (void*)wglGetProcAddress(name);
	if (p == 0 || (p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) || (p == (void*)-1)) {
		Loggers::GL->error("Failed to load function %s.", name);
	}

	return p;
}

void loadAllGLFunctions() {
	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)getGLFunctionPointer("glGenVertexArrays");
	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)getGLFunctionPointer("glBindVertexArray");
	glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)getGLFunctionPointer("glDeleteVertexArrays");

	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)getGLFunctionPointer("glEnableVertexAttribArray");
	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)getGLFunctionPointer("glDisableVertexAttribArray");
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)getGLFunctionPointer("glVertexAttribPointer");

	glGenBuffers = (PFNGLGENBUFFERSPROC)getGLFunctionPointer("glGenBuffers");
	glBindBuffer = (PFNGLBINDBUFFERPROC)getGLFunctionPointer("glBindBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC)getGLFunctionPointer("glBufferData");
	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)getGLFunctionPointer("glDeleteBuffers");

	glCreateShader = (PFNGLCREATESHADERPROC)getGLFunctionPointer("glCreateShader");
	glShaderSource = (PFNGLSHADERSOURCEPROC)getGLFunctionPointer("glShaderSource");
	glCompileShader = (PFNGLCOMPILESHADERPROC)getGLFunctionPointer("glCompileShader");
	glGetShaderiv = (PFNGLGETSHADERIVPROC)getGLFunctionPointer("glGetShaderiv");
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)getGLFunctionPointer("glGetShaderInfoLog");

	glCreateProgram = (PFNGLCREATEPROGRAMPROC)getGLFunctionPointer("glCreateProgram");
	glAttachShader = (PFNGLATTACHSHADERPROC)getGLFunctionPointer("glAttachShader");
	glLinkProgram = (PFNGLLINKPROGRAMPROC)getGLFunctionPointer("glLinkProgram");
	glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)getGLFunctionPointer("glValidateProgram");
	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)getGLFunctionPointer("glGetProgramiv");
	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)getGLFunctionPointer("glGetProgramInfoLog");
	glDetachShader = (PFNGLDETACHSHADERPROC)getGLFunctionPointer("glDetachShader");
	glDeleteShader = (PFNGLDELETESHADERPROC)getGLFunctionPointer("glDeleteShader");
	glUseProgram = (PFNGLUSEPROGRAMPROC)getGLFunctionPointer("glUseProgram");
}