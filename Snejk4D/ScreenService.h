#pragma once
#include "AbstractScreen.h"
#include "gl_includes.h"
#include "ScreenEnum.h"

class ScreenService
{
public:
	static ScreenService * getInstance();
	void SetScreen(GLFWwindow* window);
	AbstractScreen* getActualScreen() const;
private:
	ScreenService();
	AbstractScreen * actual_screen;
	void setActualScreenByEnum(GLFWwindow* window, ScreenEnum screen);
};
