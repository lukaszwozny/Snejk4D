#pragma once

#include "gl_includes.h"

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

