#include "engine.h"
#include <iostream>

#include "../display/glfw/displayglfw.h"

#include "../renderer/irenderer.h"

namespace page {

Engine::Engine(const InitData data) {
	std::cout << "PAGE engine initializing ...\n";
	mDisplay = std::make_unique<DisplayGlfw>(data.width, data.height, data.title, data.fullScreen);
}

Engine::~Engine() = default;

void Engine::Run() const {
	std::cout << "PAGE engine running ...\n";
	while (true) {
		mDisplay->Update();
	}
}

}