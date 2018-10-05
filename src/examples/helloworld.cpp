#include <iostream>
#include "../core/engine.h"

int main() {
	static_assert("C++17");
	std::cout << "Hello kewken\n";

	// Initialize
	page::InitData data;
	data.width = 1080u;
	data.height = 720u;
	data.title = "PAGE test";
	data.fullScreen = false;

	page::Engine engine(std::move(data));
	engine.Run();

	std::cin.get();
}
