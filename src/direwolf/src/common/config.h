#pragma once

namespace dwf {

enum BackendType {
    Null,
    OpenGL,
    Vulkan,
    D3D11,
    D3D12
};

enum RendererType {
    Rasterizer,
    RayTracer
};

struct PlatformData {
    void* windowHandle = nullptr;
};

struct InitData {
    RendererType rendererType;
    BackendType backendType;
};

} // namespace pgfx
