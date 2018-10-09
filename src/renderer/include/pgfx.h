#pragma once

#include <memory>
#include "irenderer.h"
#include "common/config.h"

// TODO: Should we make this a singleton, or maybe a module to PAGE?
namespace pgfx {

void Initialize(const PlatformData& platformData, const InitData& initData);
// TODO: Make private when we figure this out
static std::unique_ptr<IRenderer> m_renderer;

}
