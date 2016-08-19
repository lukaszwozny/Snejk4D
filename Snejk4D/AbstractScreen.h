#pragma once
#include "gl_includes.h"

class AbstractScreen
{
public:
	AbstractScreen(GLFWwindow* window);
	void render();
	void end();
	virtual void update() = 0;

protected:
	GLFWwindow* window;
	bool is_end;
};
