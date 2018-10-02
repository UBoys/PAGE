#pragma once

#include "../idisplay.h"
#include <string>

struct GLFWwindow;

class DisplayGlfw : public IDisplay {
public:
	DisplayGlfw();
	~DisplayGlfw();

	virtual void update() override;
private:
    void _initialize();

    bool m_fullscreen;
	GLFWwindow* m_window;
	std::string m_title;
	uint16_t m_width;
	uint16_t m_height;
};
