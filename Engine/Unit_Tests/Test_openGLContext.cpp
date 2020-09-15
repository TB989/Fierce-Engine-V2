#include "UnitTests.h"
#include "parser/Parser.h"
#include "gl/GL.h"
#include "headers/openGL/glext.h"
#include "headers/openGL/wglext.h"

typedef HGLRC WINAPI wglCreateContextAttribsARB_type(HDC hdc, HGLRC hShareContext, const int* attribList);
wglCreateContextAttribsARB_type* wglCreateContextAttribsARB=nullptr;
// See https://www.opengl.org/registry/specs/ARB/wgl_create_context.txt for all values
#define WGL_CONTEXT_MAJOR_VERSION_ARB             0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB             0x2092
#define WGL_CONTEXT_PROFILE_MASK_ARB              0x9126
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB          0x00000001

typedef BOOL WINAPI wglChoosePixelFormatARB_type(HDC hdc, const int* piAttribIList, const FLOAT * pfAttribFList, UINT nMaxFormats, int* piFormats, UINT * nNumFormats);
wglChoosePixelFormatARB_type* wglChoosePixelFormatARB=nullptr;
// See https://www.opengl.org/registry/specs/ARB/wgl_pixel_format.txt for all values
#define WGL_DRAW_TO_WINDOW_ARB                    0x2001
#define WGL_ACCELERATION_ARB                      0x2003
#define WGL_SUPPORT_OPENGL_ARB                    0x2010
#define WGL_DOUBLE_BUFFER_ARB                     0x2011
#define WGL_PIXEL_TYPE_ARB                        0x2013
#define WGL_COLOR_BITS_ARB                        0x2014
#define WGL_DEPTH_BITS_ARB                        0x2022
#define WGL_STENCIL_BITS_ARB                      0x2023
#define WGL_ALPHA_BITS_ARB                        0x201B
#define WGL_FULL_ACCELERATION_ARB                 0x2027
#define WGL_TYPE_RGBA_ARB                         0x202B

HGLRC context;
HDC hdc;

PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray;

PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;

PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLBUFFERDATAPROC glBufferData;

PFNGLCREATESHADERPROC glCreateShader;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;

PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLGETPROGRAMIVPROC glGetProgramiv;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
PFNGLDETACHSHADERPROC glDetachShader;
PFNGLDELETESHADERPROC glDeleteShader;
PFNGLUSEPROGRAMPROC glUseProgram;

GLuint vaoId;
GLuint vboId;

GLuint vsId;
GLuint fsId;
GLuint pId;

void* GetAnyGLFuncAddress(const char* name){
	void* p = (void*)wglGetProcAddress(name);
	if (p == 0 ||(p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) ||(p == (void*)-1)){
		Loggers::GL->error("Failed to load function %s.",name);
	}

	return p;
}

Test_openGLContext::Test_openGLContext() {
	eventSystem->addListener(this, &Test_openGLContext::onAppInit);
	eventSystem->addListener(this, &Test_openGLContext::onAppUpdate);
	eventSystem->addListener(this, &Test_openGLContext::onAppCleanUp);

	eventSystem->addListener(this, &Test_openGLContext::onWindowResize);
}

void Test_openGLContext::onAppInit(AppInitEvent* event) {
	std::map<std::string, std::string> settings = Parser::parsePropertiesFile("C:/Users/Tobias/Desktop/GameEngine/Engine/Engine.ini");
	m_settings.parse(settings);

	windowSystem = new WindowSystem(this, m_settings);

	//Dummy
	window = windowSystem->createDummyWindow();
	HDC dummy_hdc = GetDC(window->getHandle());

	PIXELFORMATDESCRIPTOR pfd = {};
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.cColorBits = 32;
	pfd.cAlphaBits = 8;
	pfd.cDepthBits = 24;

	int format = ChoosePixelFormat(dummy_hdc, &pfd);
	if (!format) {
		Loggers::CORE->error("Failed to find pixel format for dummy context.");
	}
	if (!SetPixelFormat(dummy_hdc, format, &pfd)) {
		Loggers::CORE->error("Failed to set pixel format for dummy context.");
	}

	HGLRC dummy_context = wglCreateContext(dummy_hdc);
	if (!dummy_context) {
		Loggers::CORE->error("Failed to create dummy context.");
	}
	if (!wglMakeCurrent(dummy_hdc, dummy_context)) {
		Loggers::CORE->error("Failed make dummy context current.");
	}

	wglCreateContextAttribsARB = (wglCreateContextAttribsARB_type*)wglGetProcAddress("wglCreateContextAttribsARB");
	if (wglCreateContextAttribsARB==nullptr) {
		Loggers::CORE->error("Failed to load wglCreateContextAttribsARB.");
	}
	wglChoosePixelFormatARB = (wglChoosePixelFormatARB_type*)wglGetProcAddress("wglChoosePixelFormatARB");
	if (wglChoosePixelFormatARB == nullptr) {
		Loggers::CORE->error("Failed to load wglCreateContextAttribsARB.");
	}

	wglMakeCurrent(dummy_hdc, 0);
	wglDeleteContext(dummy_context);
	ReleaseDC(window->getHandle(), dummy_hdc);
	DestroyWindow(window->getHandle());
	delete window;

	//Window
	window = windowSystem->createWindow();
	hdc = GetDC(window->getHandle());

	int pixel_format_attribs[] = {
		WGL_DRAW_TO_WINDOW_ARB,     GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB,     GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB,      GL_TRUE,
		WGL_ACCELERATION_ARB,       WGL_FULL_ACCELERATION_ARB,
		WGL_PIXEL_TYPE_ARB,         WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB,         32,
		WGL_ALPHA_BITS_ARB,         8,
		WGL_DEPTH_BITS_ARB,         24,
		WGL_STENCIL_BITS_ARB,       8,
		0
	};
	int pixel_format;
	UINT num_formats;
	wglChoosePixelFormatARB(hdc, pixel_format_attribs, 0, 1, &pixel_format, &num_formats);
	if (!num_formats) {
		Loggers::CORE->error("Failed to choose pixel format.");
	}
	DescribePixelFormat(hdc, pixel_format, sizeof(pfd), &pfd);
	if (!SetPixelFormat(hdc, pixel_format, &pfd)) {
		Loggers::CORE->error("Failed to set pixel format.");
	}

	int attribs[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 3,
		WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0,
	};
	context = wglCreateContextAttribsARB(hdc, 0, attribs);
	if (!context) {
		Loggers::CORE->error("Failed to create context.");
	}
	if (!wglMakeCurrent(hdc, context)) {
		Loggers::CORE->error("Failed to make current context.");
	}

	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)GetAnyGLFuncAddress("glGenVertexArrays");
	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)GetAnyGLFuncAddress("glBindVertexArray");

	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)GetAnyGLFuncAddress("glEnableVertexAttribArray");
	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)GetAnyGLFuncAddress("glDisableVertexAttribArray");
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)GetAnyGLFuncAddress("glVertexAttribPointer");

	glGenBuffers = (PFNGLGENBUFFERSPROC)GetAnyGLFuncAddress("glGenBuffers");
	glBindBuffer = (PFNGLBINDBUFFERPROC)GetAnyGLFuncAddress("glBindBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC)GetAnyGLFuncAddress("glBufferData");

	glCreateShader = (PFNGLCREATESHADERPROC)GetAnyGLFuncAddress("glCreateShader");
	glShaderSource = (PFNGLSHADERSOURCEPROC)GetAnyGLFuncAddress("glShaderSource");
	glCompileShader = (PFNGLCOMPILESHADERPROC)GetAnyGLFuncAddress("glCompileShader");
	glGetShaderiv = (PFNGLGETSHADERIVPROC)GetAnyGLFuncAddress("glGetShaderiv");
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)GetAnyGLFuncAddress("glGetShaderInfoLog");

	glCreateProgram = (PFNGLCREATEPROGRAMPROC)GetAnyGLFuncAddress("glCreateProgram");
	glAttachShader = (PFNGLATTACHSHADERPROC)GetAnyGLFuncAddress("glAttachShader");
	glLinkProgram = (PFNGLLINKPROGRAMPROC)GetAnyGLFuncAddress("glLinkProgram");
	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)GetAnyGLFuncAddress("glGetProgramiv");
	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)GetAnyGLFuncAddress("glGetProgramInfoLog");
	glDetachShader = (PFNGLDETACHSHADERPROC)GetAnyGLFuncAddress("glDetachShader");
	glDeleteShader = (PFNGLDELETESHADERPROC)GetAnyGLFuncAddress("glDeleteShader");
	glUseProgram = (PFNGLUSEPROGRAMPROC)GetAnyGLFuncAddress("glUseProgram");

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
	std::ifstream vsStream("C:/Users/Tobias/Desktop/GameEngine/Engine/ressources/shaders/openGL/MyFirstShader.vert", std::ios::in);
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
	std::ifstream fsStream("C:/Users/Tobias/Desktop/GameEngine/Engine/ressources/shaders/openGL/MyFirstShader.frag", std::ios::in);
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
	if (InfoLogLength > 0) {
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
	if (InfoLogLength > 0) {
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
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(pId, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		Loggers::GL->error("%s\n", &ProgramErrorMessage[0]);
	}

	window->show();
}

void Test_openGLContext::onAppUpdate(AppUpdateEvent* event) {
	window->pollEvents();

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

	SwapBuffers(hdc);
}

void Test_openGLContext::onAppCleanUp(AppCleanUpEvent* event) {
	wglMakeCurrent(hdc, 0);
	wglDeleteContext(context);
	ReleaseDC(window->getHandle(), hdc);
	delete window;
	delete windowSystem;
}

void Test_openGLContext::onWindowResize(WindowResizeEvent* event) {
	Loggers::CORE->info("Resize to [%ix%i]", event->m_width, event->m_height);
}