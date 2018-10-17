#pragma once

#include "irendercontext.h"

namespace dwf {

struct PlatformData;

class RenderContextOSX final : public IRenderContext {
public:
    RenderContextOSX(const PlatformData& platformData);
    virtual ~RenderContextOSX() override;
    void SwapBuffers() const;
private:
    void* m_context;
    void* m_view;
};

}  // namespace dwf
