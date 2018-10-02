#include <iostream>
#include "../core/engine.h"
#include "../renderer/renderer.h"
#include "../display/glfw/displayglfw.h"

int main() {
	static_assert("C++17");
	std::cout << "Hello kewken\n";

	Engine e;
	Renderer r;
	std::unique_ptr<IDisplay> display = std::make_unique<DisplayGlfw>();

	while (true) {
		display->update();
	}

	std::cin.get();
}
