#pragma once

namespace pgfx {

enum RendererType {
	Null,
	OpenGL,
	Vulkan,
	D3D11,
	D3D12
};

struct PlatformData {
	void* windowHandle = nullptr;
};

struct InitData {
	RendererType preferredRenderer = Null;
};
	
} // namespace pgfx
