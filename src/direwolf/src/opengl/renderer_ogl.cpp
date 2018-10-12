#include <iostream>
#include "common/config.h"
#include "renderer_ogl.h"

#include <GL/glew.h>
#include <GL/wglew.h>
#include <windows.h>

namespace {
	
	
	PIXELFORMATDESCRIPTOR pixelFormatFake;
	HGLRC renderContextFake; // vars to init glew
	HDC deviceContextFake;
	HWND hwndFake;

	PIXELFORMATDESCRIPTOR pixelFormat;
	HGLRC renderContext; // vars to init glew
	HDC deviceContext;
	HWND hwnd;
	//HGLRC hrc1; //vars for the real window
	//HDC hdc1;
	//HWND hwnd1;
}

namespace dwf {

void RendererOGL::Initialize(const RendererCaps& caps, const PlatformData& platformData) {
    std::cout << "DireWolf: Initializing OpenGL Renderer\n";

	// Dummy window to peek into WGL functionality.
	//
	// An application can only set the pixel format of a window one time.
	// Once a window's pixel format is set, it cannot be changed.
	//// MSDN: http://msdn.microsoft.com/en-us/library/windows/desktop/dd369049%28v=vs.85%29.aspx
	//HWND hwnd = CreateWindowA("STATIC"
	//	, ""
	//	, WS_POPUP|WS_DISABLED
	//	, -32000
	//	, -32000
	//	, 0
	//	, 0
	//	, NULL
	//	, NULL
	//	, GetModuleHandle(NULL)
	//	, 0
	//	);

	//HDC hdc = GetDC(hwnd);
	//HGLRC context = wglCreateContext(hdc);

	int error;
	
	hwnd = static_cast<HWND>(platformData.windowHandle);

	hwndFake = CreateWindowA("STATIC"
				, ""
				, WS_POPUP|WS_DISABLED
				, -32000
				, -32000
				, 0
				, 0
				, NULL
				, NULL
				, GetModuleHandle(NULL)
				, 0
				);

	// Initialize extensions
	// Get the device context
	deviceContextFake = GetDC(hwndFake);
	if (!deviceContextFake) {
		std::cerr << "bajs";
	}
	// Set a temporary pixel format
	error = SetPixelFormat(deviceContextFake, 11, &pixelFormat);
	if (error != 1) {
		std::cerr << "bjas";
	}
	// Create temporary render context
	renderContextFake = wglCreateContext(deviceContextFake);
	if (!renderContextFake) {
		std::cerr << "fudge";
	}
	// Set the temporary rendering context as the current rnedering context for this window
	error = wglMakeCurrent(deviceContextFake, renderContextFake);
	if(error != 1) {
		std::cerr <<"fuck";
	}
	// Initialize the OpenGL extensions needed for this app, we need a temp context to do so
	GLenum err = glewInit();
    if (err != GLEW_OK) {
		std::cerr << "Failed to initialize extensions\n"; 
	}

	// Release the temporary render context now that the extensions have loaded
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(renderContextFake);
	renderContextFake = NULL;


	// Release device context
	ReleaseDC(hwndFake, deviceContextFake);
	deviceContextFake = 0;


	// Get the device context again
	deviceContext = GetDC(hwnd);
	if (!deviceContext) {
		std::cerr << "hejs";
	}

	int32_t attrs[] =
				{
					WGL_SAMPLE_BUFFERS_ARB, 0,
					WGL_SAMPLES_ARB, 0,
					WGL_SUPPORT_OPENGL_ARB, true,
					WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
					WGL_DRAW_TO_WINDOW_ARB, true,
					WGL_DOUBLE_BUFFER_ARB, true,
					WGL_COLOR_BITS_ARB, 32,
					WGL_DEPTH_BITS_ARB, 24,
					WGL_STENCIL_BITS_ARB, 8,
					0
				};
	
	int pixelFormat1[1];
	unsigned int formatCount;
	// Query for a pixel format that fits the attributes we want
	error = wglChoosePixelFormatARB(deviceContext, attrs, NULL, 1, pixelFormat1, &formatCount);
	if(error != 1) {
		std::cerr <<"fuck";
	}

	// If the gpu/display can handle the desired pixel format we set it as the current one
	error = SetPixelFormat(deviceContext, pixelFormat1[0], &pixelFormat);
	if (error != 1) {
		std::cerr << "fuck";
	}
	//DestroyWindow(hwnd);
	//hwnd = nullptr;

	int attributeList[5];
	// Set the 4.0 version of OpenGL in the attribute list.
	attributeList[0] = WGL_CONTEXT_MAJOR_VERSION_ARB;
	attributeList[1] = 4;
	attributeList[2] = WGL_CONTEXT_MINOR_VERSION_ARB;
	attributeList[3] = 0;
	// Null terminate the attribute list.
	attributeList[4] = 0;
	renderContext = wglCreateContextAttribsARB(deviceContext, 0, attributeList);
	if (!renderContext) {
		std::cerr << "fudge";
	}
	error = wglMakeCurrent(deviceContext, renderContext);
	if(error != 1) {
		std::cerr <<"fuck";
	}

	// Get the name of the video card.
	const char* vendorString = (char*)glGetString(GL_VENDOR);

	// Turn on or off the vertical sync depending on the input bool value.
	if(true) {
		wglSwapIntervalEXT(1);
	}
	else {
		wglSwapIntervalEXT(0);
	}

	// Initialize context
}

}  // namespace pgfx
