#include <iostream>
#include "../core/engine.h"
#include "../renderer/renderer.h"

int main() {
	static_assert("C++17");
	std::cout << "Hello kewken\n";

	Engine e;
	Renderer r;
	std::cin.get();
}
