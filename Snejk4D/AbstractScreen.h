#pragma once
#include "gl_includes.h"

class AbstractScreen
{
public:
	AbstractScreen(GLFWwindow* window);
	void end();
	virtual void render() = 0;
	virtual void setBackgroundColor();

protected:
	GLFWwindow* window;
	bool is_end;
};
