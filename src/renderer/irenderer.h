#pragma once

namespace molten {

enum RendererType {
    Null,
    OpenGL,
    Vulkan,
    D3D12
};

enum RenderCommand {
    SetPipelineState,
    SetVertexBuffer,
    SetIndexBuffer,
    SetTextures,
    SetSamplers,
    DrawIndexed
};

struct RendererCaps {
    RendererType type;
    void* allocator;
    bool debug;
    bool msaa;
};

struct TextureDescription {};
struct SamplerDescription {};
// Should contain rasterizer state, depth stencil state, blend state and shader
struct PipelineState {};
// TODO: Constant buffers

// Handle for each renderer resource.
// All rendering resources are owned the renderer and should not be coupled with client code
struct MoltenObject {
    MoltenObject() { objectId = ++s_objectIds;};
    bool IsValid() { return objectId != 0; }
    uint32_t objectId = 0;
    static uint32_t s_objectIds;
};

class IRenderer {
public:
    virtual ~IRenderer() = default;

    virtual void Initialize(const RendererCaps& caps);

    virtual MoltenObject CreateVertexBuffer(const uint32_t count) = 0;
    virtual MoltenObject CreateIndexBuffer(uint32_t count) = 0;
    virtual MoltenObject CreatePipelineState(const PipelineState& state);
    virtual MoltenObject CreateTexture(const TextureDescription& description, const std::vector<void*> data);
    virtual MoltenObject CreateSamplerState(const SamplerDescription& description);

    virtual void* MapVertexBuffer(const MoltenObject& handle) = 0;
    virtual void* MapIndexBuffer(const MoltenObject& handle) = 0;
    virtual void UnmapVertexBuffer(const MoltenObject& handle, const uint32_t count) = 0;
    virtual void UnmapIndexBuffer(const MoltenObject& handle, const uint32_t count) = 0; 

    virtual void DestroyVertexBuffer(const MoltenObject& handle) = 0;
    virtual void DestroyIndexBuffer(const MoltenObject& handle) = 0;
    virtual void DestroyTexture(const MoltenObject& handle) = 0;
    virtual void DestroyPipelineState(const MoltenObject& handle) = 0;
    virtual void DestroySamplerState(const MoltenObject& hanele) = 0;

    /// Actual rendering commands that operate on updated and ready resources.
    virtual void Render(const std::vector<RenderCommand> commandBuffer) = 0;
};

} 