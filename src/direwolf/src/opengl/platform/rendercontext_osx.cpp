#if defined(__APPLE__)

#include "rendercontext_osx.h"
#include <iostream>

namespace dwf {

RenderContextOSX::RenderContextOSX(const PlatformData& platformData) {
    std::cout << "Direwolf: Setting up render context for OSX\n";
};

}  // namespace dwf

#endif
