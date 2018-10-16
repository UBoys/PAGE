#if defined(__APPLE__)

#include "rendercontext_osx.h"
#include "common/config.h"
#include <iostream>
#include <Cocoa/Cocoa.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>

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
	NSOpenGLView* glView = [[NSOpenGLView alloc] initWithFrame:glViewRect pixelFormat:pixelFormat];
    if (!glView) {
         std::cerr << "fuck2";
    }
    [pixelFormat release];

    // GLFW creates a helper contentView that handles things like keyboard and drag and
    // drop events. We don't want to clobber that view if it exists. Instead we just
    // add ourselves as a subview and make the view resize automatically.
    NSView *contentView = [nsWindow contentView];
    if (contentView) {
         [glView setAutoresizingMask:( NSViewHeightSizable |
                 NSViewWidthSizable |
                 NSViewMinXMargin |
                 NSViewMaxXMargin |
                 NSViewMinYMargin |
                 NSViewMaxYMargin )];
         [contentView addSubview:glView];
    }
    else {
         std::cerr << "fuck?\n";
         [nsWindow setContentView:glView];
    }

    NSOpenGLContext* glContext = [glView openGLContext];
    if (!glContext) {
        std::cerr << "Fuck no context\n";
    }
    [glContext makeCurrentContext];
	GLint interval = 0;
	[glContext setValues:&interval forParameter:NSOpenGLCPSwapInterval];

    // When initializing NSOpenGLView programatically (as we are), this sometimes doesn't
    // get hooked up properly (especially when there are existing window elements). This ensures
    // we are valid. Otherwise, you'll probably get a GL_INVALID_FRA_EBUFFER_OPERATION when
    // trying to glClear() for the first time.
    [glContext setView:glView];

    m_view = glView;
    m_context = glContext;

    // Get the name of the video card.
    auto vendorString = static_cast<const uint8_t*>(glGetString(GL_VENDOR));
	auto versionString = static_cast<const uint8_t*>(glGetString(GL_VERSION));

    std::cout << "DireWolf: Successfully set up OpenGL context with GPU " << vendorString << std::endl;
    std::cout << "DireWolf: Running OpenGL version " << versionString << std::endl;
};

RenderContextOSX::~RenderContextOSX() {
    NSOpenGLView* glView = static_cast<NSOpenGLView*>(m_view);
    [glView release];
    m_view = nullptr;
    m_context = nullptr;
}

void RenderContextOSX::Swap() const {
    NSOpenGLContext* glContext = static_cast<NSOpenGLContext*>(m_context);
    [glContext makeCurrentContext];
	[glContext flushBuffer];
}

}  // namespace dwf

#endif
