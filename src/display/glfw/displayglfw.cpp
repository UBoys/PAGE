#include "displayglfw.h"

#include <GLFW/glfw3.h>
#include <iostream>

namespace {
    void _callbackError(int error, const char *description) { } // TODO: Implement
}

DisplayGlfw::DisplayGlfw(const uint16_t width, const uint16_t height, const std::string title,
                         const bool fullscreen)
    : m_width(width), m_height(height), m_title(title), m_fullscreen(fullscreen)
{
    _Initialize();
}

DisplayGlfw::~DisplayGlfw() {
    // Free the window callbacks and destroy the window.
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void DisplayGlfw::_Initialize() {
    glfwSetErrorCallback(_callbackError);

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
