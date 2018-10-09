#include "engine.h"
#include <iostream>

#include "../display/glfw/displayglfw.h"
#include "pgfx.h"

#define USE_GLFW

namespace page {

Engine::Engine(const InitData data) {
    std::cout << "PAGE: Engine initializing ...\n";
    m_display = std::make_unique<DisplayGlfw>(data.width, data.height, data.title, data.fullScreen);
    // Setup renderer
    pgfx::InitData initData { pgfx::RendererType::OpenGL };
    pgfx::PlatformData platformData = { m_display->GetNativeWindowHandle() };
    pgfx::Initialize(platformData, initData);
}

Engine::~Engine() = default;

void Engine::Run() const {
    std::cout << "PAGE: Engine running ...\n";
    while (true) {
        m_display->Update();
    }
}

}
