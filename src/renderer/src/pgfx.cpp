#include "pgfx.h"
#include <iostream>
// TODO: Build definitions should decide what we include and build
#include "opengl/renderer_ogl.h"

namespace pgfx {

void Initialize(const PlatformData& platformData, const InitData& initData) {
	std::cout << "PGFX: Initializing render library!\n";
    RendererCaps caps = {};
    switch (initData.preferredRenderer) {
        case RendererType::OpenGL:
            m_renderer = std::make_unique<RendererOGL>();
            m_renderer->Initialize(caps, platformData, initData);
            break;
        case RendererType::Vulkan:
            // TODO: Callbam
			std::cerr << "No vulkan renderer implemented yet!";
            break;
        default:
            std::cerr << "What are you doing\n";
    }
}

}  // namespace pgfx
