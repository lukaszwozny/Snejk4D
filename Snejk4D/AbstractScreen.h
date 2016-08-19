#pragma once
#include "gl_includes.h"

class AbstractScreen
{
public:
	AbstractScreen(GLFWwindow* window);
	virtual void render() = 0;
	virtual void setBackgroundColor();

protected:
	GLFWwindow* window;
};
