#pragma once

#include "irenderer.h"

namespace pgfx {

struct PlatformData;
struct InitData;
class RendererOGL final : public IRenderer {
public:
    virtual void Initialize(const RendererCaps& caps, const PlatformData& data, const InitData& initData) final;

    virtual GfxObject CreateVertexBuffer(const uint32_t count) { return GfxObject(); };
    virtual GfxObject CreateIndexBuffer(const uint32_t count) { return GfxObject(); };
    virtual GfxObject CreatePipelineState(const PipelineState& state) { return GfxObject(); };
    virtual GfxObject CreateTexture(const TextureDescription& description,
                                    const std::vector<void*>& data) { return GfxObject();};
    virtual GfxObject CreateSamplerState(const SamplerDescription& description) { return GfxObject(); };

    virtual void* MapVertexBuffer(const GfxObject& handle) { return nullptr; };
    virtual void* MapIndexBuffer(const GfxObject& handle) { return nullptr; };
    virtual void UnmapVertexBuffer(const GfxObject& handle, const uint32_t count) {};
    virtual void UnmapIndexBuffer(const GfxObject& handle, const uint32_t count) {};

    virtual void DestroyVertexBuffer(const GfxObject& handle) {};
    virtual void DestroyIndexBuffer(const GfxObject& handle) {};
    virtual void DestroyTexture(const GfxObject& handle) {};
    virtual void DestroyPipelineState(const GfxObject& handle) {};
    virtual void DestroySamplerState(const GfxObject& hanele) {};

    // Actual rendering commands that operate on updated and ready resources.
    virtual void Render(const std::vector<RenderCommand>& commandBuffer){};
};

}  // namespace pgfx
