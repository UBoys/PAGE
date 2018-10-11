#include "direwolf/renderengine.h"
#include <iostream>

int main() {
    // Setup renderer
    dwf::InitData initData { dwf::RendererType::Rasterizer, dwf::BackendType::Vulkan };
    dwf::PlatformData platformData = { nullptr };
    auto engine = std::make_unique<dwf::RenderEngine>(platformData, initData);

    std::cin.get();
    return 0;
}
