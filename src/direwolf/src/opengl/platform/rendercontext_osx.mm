#if defined(__APPLE__)


#include "rendercontext_osx.h"

#include "common/config.h"
#include <iostream>
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>
#include <Cocoa/Cocoa.h>

namespace dwf {

RenderContextOSX::RenderContextOSX(const PlatformData& platformData) {
    std::cout << "Direwolf: Setting up render context for OSX\n";
    NSWindow* nsWindow = (NSWindow*)(platformData.windowHandle);

    if (!nsWindow) {
        std::cerr << "fuck";


    }

    NSOpenGLPixelFormatAttribute profile = NSOpenGLProfileVersion3_2Core;
    NSOpenGLPixelFormatAttribute pixelFormatAttributes[] = {
        NSOpenGLPFAOpenGLProfile, profile,
        NSOpenGLPFAColorSize,     24,
        NSOpenGLPFAAlphaSize,     8,
        NSOpenGLPFADepthSize,     24,
        NSOpenGLPFAStencilSize,   8,
        NSOpenGLPFADoubleBuffer,  true,
        NSOpenGLPFAAccelerated,   true,
        NSOpenGLPFANoRecovery,    true,
        0,                        0,
    };

    NSOpenGLPixelFormat* pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:pixelFormatAttributes];
    if (!pixelFormat) {
        std::cerr << "fuck";
    }

    NSRect glViewRect = [[nsWindow contentView] bounds];
    //NSOpenGLView* glView;// = [[NSOpenGLView alloc] initWithFrame:glViewRect pixelFormat:pixelFormat];
    //if (!glView) {
     //   std::cout << "fuck";
    //}
    //[pixelFormat release];


    std::cout << "All good";

};

}  // namespace dwf

#endif
