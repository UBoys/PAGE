#pragma once

#include <windows.h>
#include "irendercontext.h"

namespace dwf {

struct PlatformData;

class RenderContextWin final : public IRenderContext {
public:
    RenderContextWin(const PlatformData& platformData);
    virtual void SwapBuffers() const override{};
};

}  // namespace dwf
