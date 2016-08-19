#pragma once

//// Include GLEW
#include <GL/glew.h>

//// Include GLFW3
#include <glfw3.h>

//// Include GLM
#include <glm/glm.hpp>
#include "GameStateEnum.h"
#include "MainMenuScreen.h"

class Game
{
public:
	static GameStateEnum game_state_enum;

	int Initialize();
	void update();
	void render();

private:
	MainMenuScreen* menu_screen;
	GLFWwindow* window;

	int initGLFWwindow();
	int initGLFW();
};

