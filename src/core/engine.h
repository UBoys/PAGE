#pragma once
#include <iostream>
#include <memory>

class IDisplay;
namespace dwf {
	class RenderEngine;
}

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
    std::unique_ptr<IDisplay> m_display;
	std::unique_ptr<dwf::RenderEngine> m_renderEngine;
};

} // namespace page
