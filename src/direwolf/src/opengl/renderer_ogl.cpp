#include <iostream>
#include "common/config.h"
#include "renderer_ogl.h"
#ifdef _WIN32
#include "opengl/rendercontext_wgl.h"
#endif

namespace dwf {

RendererOGL::RendererOGL() = default;
RendererOGL::~RendererOGL() = default;

void RendererOGL::Initialize(const RendererCaps& caps, const PlatformData& platformData) {
    std::cout << "DireWolf: Initializing OpenGL Renderer\n";
#ifdef _WIN32
	m_renderContext = std::make_unique<RenderContextWGL>(platformData);
#endif
	// Initialize context
}

}  // namespace pgfx
