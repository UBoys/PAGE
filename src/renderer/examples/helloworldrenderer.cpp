#include "pgfx.h"
#include <iostream>

int main() {
	// Setup renderer
    pgfx::InitData initData = { pgfx::RendererType::Vulkan };
    pgfx::PlatformData platformData = { nullptr };

	pgfx::Initialize(platformData, initData);

	std::cin.get();
	return 0;
}
