#pragma once

#include "../idisplay.h"
#include <string>

struct GLFWwindow;

class DisplayGlfw final : public IDisplay {
public:
    DisplayGlfw(const uint16_t width, const uint16_t height, const std::string title, const bool fullscreen);
    virtual ~DisplayGlfw() override;

    virtual void* GetNativeWindowHandle() const override;
    virtual void Update() const override;
private:
    void _Initialize();

    bool m_fullscreen;
    GLFWwindow* m_window;
    std::string m_title;
    uint16_t m_width;
    uint16_t m_height;
};
