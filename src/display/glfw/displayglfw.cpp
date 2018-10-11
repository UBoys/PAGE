#include "displayglfw.h"

#include <GLFW/glfw3.h>

#if defined(_WIN32)
	#define GLFW_EXPOSE_NATIVE_WIN32
#endif
#include <GLFW/glfw3native.h>

#include <iostream>

namespace {
	void _CallbackError(int error, const char *description) { } // TODO: Implement
	void* _GetGlfwNativeWindowhandle(GLFWwindow* window) {
#if defined _WIN32
		return static_cast<void*>(glfwGetWin32Window(window));
#endif
	}
}

DisplayGlfw::DisplayGlfw(const uint16_t width, const uint16_t height, const std::string title, const bool fullscreen)
	: m_width(width), m_height(height), m_title(title), m_fullscreen(fullscreen)
{
	_Initialize();
}

DisplayGlfw::~DisplayGlfw() {
	// Free the window callbacks and destroy the window.
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void* DisplayGlfw::GetNativeWindowHandle() const {
	return _GetGlfwNativeWindowhandle(m_window);
}

void DisplayGlfw::_Initialize() {
	glfwSetErrorCallback(_CallbackError);

	if (!glfwInit()) {
		fprintf(stderr, "GLFW error: Failed to initialize!\n");
	}

	// Configures the window.
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);  // The window will stay hidden until after creation
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE); // The window will be resizable if not fullscreen
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Disable context creation

	// For new GLFW, and macOS.
	glfwWindowHint(GLFW_STENCIL_BITS, 8);	// Fixes 16 bit stencil bits in macOS.
	glfwWindowHint(GLFW_STEREO, GLFW_FALSE); // No stereo view!

	// Create a windowed mode window with no context
	m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
	if (m_window == nullptr) {
		// TODO: Handle error
		glfwTerminate();
	}

	// Shows the glfw window.
	glfwShowWindow(m_window);
}

void DisplayGlfw::Update() const {
	glfwPollEvents();
}
