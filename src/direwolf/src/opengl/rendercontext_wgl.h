#pragma once

#include "irenderer.h"
#include <windows.h>

namespace dwf {

struct PlatformData;

class RenderContextWGL {
public:
	RenderContextWGL(const PlatformData& platformData);

private:
	void _SetupFakeContext();
	void _SetupRealContext(const PlatformData& platformData);

	PIXELFORMATDESCRIPTOR m_pixelFormat;
	HGLRC m_renderContext;
	HDC m_deviceContext;
	HWND m_hwnd;
};

}  // namespace dwf
