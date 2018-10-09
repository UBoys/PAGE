#include "direwolf/renderengine.h"

#include <iostream>
// TODO: Build definitions should decide what we include and build
#include "opengl/renderer_ogl.h"

namespace dwf {

RenderEngine::RenderEngine(const PlatformData& platformData, const InitData& initData){
    switch(initData.rendererType) {
        case RendererType::Rasterizer:
            _SetupRasterizer(platformData, initData.backendType);
            break;
        case RendererType::RayTracer:
            std::cerr << "Not implemented yet\n";
            break;
        default:
            std::cerr << "Unknown renderer type\n";
    }
}

void RenderEngine::_SetupRasterizer(const PlatformData& platformData, const BackendType& type) {
    std::cout << "DireWolf: Initializing render library!\n";
    RendererCaps caps = {};
    switch (type) {
        case BackendType::OpenGL:
            m_renderer = std::make_unique<RendererOGL>();
            m_renderer->Initialize(caps, platformData);
            break;
        case BackendType::Vulkan:
            // TODO: Callbam
            std::cerr << "No vulkan renderer implemented yet!\n";
            break;
        default:
            std::cerr << "What are you doing\n";
    }
}

}  // namespace pgfx
