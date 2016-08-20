#pragma once
#include "AbstractScreen.h"
#include "gl_includes.h"
#include "ScreenEnum.h"

class ScreenService
{
public:
	static ScreenService * getInstance();
	void setScreen(GLFWwindow* window, ScreenEnum screen);
	AbstractScreen* getActualScreen() const;
private:
	AbstractScreen * actual_screen;
	void setActualScreenByEnum(GLFWwindow* window, ScreenEnum screen);
};
