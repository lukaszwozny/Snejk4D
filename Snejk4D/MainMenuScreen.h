#pragma once
#include <glfw3.h>
#include "GameStateEnum.h"

class MainMenuScreen
{
public:
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
private:
	static GameStateEnum getMouseState(GLFWwindow* window);
};
