#include "engine.h"
#include <iostream>

#include "direwolf/renderengine.h"
#include "../display/glfw/displayglfw.h"

namespace page {

Engine::Engine(const InitData data) {
    std::cout << "PAGE: Engine initializing ...\n";
    m_display = std::make_unique<DisplayGlfw>(data.width, data.height, data.title, data.fullScreen);

    dwf::InitData initData { dwf::RendererType::Rasterizer, dwf::BackendType::OpenGL };
    dwf::PlatformData platformData = { m_display->GetNativeWindowHandle() };
    m_renderEngine = std::make_unique<dwf::RenderEngine>(platformData, initData);
}

Engine::~Engine() = default;

void Engine::Run() const {
    std::cout << "PAGE: Engine running ...\n";

    while (true) {
        m_display->Update();
    }
}

}
