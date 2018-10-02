#pragma once
#include <iostream>

class IDisplay;

namespace page {

// TODO: Move
struct InitData {
	uint16_t width;
	uint16_t height;
	std::string title;
	bool fullScreen;
};

class Engine {
public:
	Engine(const InitData initData);
	~Engine();

	void Run() const;
private:
	std::unique_ptr<IDisplay> mDisplay;
};

} // namespace page
