#pragma once
#include "gl_includes.h"

class AbstractScreen
{
public:
	AbstractScreen(GLFWwindow* window);
	void render();
	virtual void update() = 0;

protected:
	GLFWwindow* window;
};
