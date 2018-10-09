#include <iostream>
#include "common/config.h"
#include "renderer_ogl.h"

namespace pgfx {

void RendererOGL::Initialize(const RendererCaps& caps, const PlatformData& platformData,
                             const InitData& initData) {
    std::cout << "PGFX: Initializing OpenGL Renderer\n";
}

}  // namespace pgfx
