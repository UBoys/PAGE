#pragma once

#include "irendercontext.h"

namespace dwf {

struct PlatformData;

class RenderContextOSX final : public IRenderContext {
public:
    RenderContextOSX(const PlatformData& platformData);
    // virtual ~RenderContextOSX() override;
    virtual void CreateContext() override {}
};

}  // namespace dwf
