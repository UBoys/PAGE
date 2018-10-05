#include <iostream>
#include "../core/engine.h"
#include "../renderer/renderer.h"
#include "renderer/vulkan/vulkansetup.h"

using namespace page;

int main() {
	static_assert("C++17");
	std::cout << "Hello kewken\n";

	Engine e;
	Renderer r;

    vulkan::TempVulkanSetupObject vulkanInitObj;

    std::cout << (vulkanInitObj.isValid() ?
        "Vulkan was successfully initialized\n" :
        "ERROR: Vulkan initialization failed\n");

    std::cout << "\n\nPress enter to EXIT";
	std::cin.get();
}
