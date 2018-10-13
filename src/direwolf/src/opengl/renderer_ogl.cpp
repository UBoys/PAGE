#include "renderer_ogl.h"
#include <iostream>
#include "common/config.h"
#include "irendercontext.h"

#if defined(_WIN32)
	#include "opengl/platform/rendercontext_win.h"
#elif defined(__APPLE__)
	#include "opengl/platform/rendercontext_osx.h"
#endif
namespace dwf {

RendererOGL::RendererOGL() = default;
RendererOGL::~RendererOGL() = default;

void RendererOGL::Initialize(const RendererCaps& caps, const PlatformData& platformData) {
    std::cout << "DireWolf: Initializing OpenGL Renderer\n";
#if defined(_WIN32)
	m_renderContext = std::make_unique<RenderContextWin>(platformData);
#elif defined(__APPLE__)
	m_renderContext = std::make_unique<RenderContextOSX>(platformData);
#endif
	// Initialize context
}

}  // namespace pgfx
