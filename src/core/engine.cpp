#include "engine.h"
#include <iostream>

#include "../display/glfw/displayglfw.h"
#include "pgfx.h"

namespace page {

Engine::Engine(const InitData data) {
	std::cout << "PAGE engine initializing ...\n";
	mDisplay = std::make_unique<DisplayGlfw>(data.width, data.height, data.title, data.fullScreen);

	pgfx::MainRenderer r;
	r.Foo();
}

Engine::~Engine() = default;

void Engine::Run() const {
	std::cout << "PAGE engine running ...\n";
	while (true) {
		mDisplay->Update();
	}
}

}