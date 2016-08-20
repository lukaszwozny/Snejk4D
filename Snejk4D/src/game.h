#pragma once

#include "gl_includes.h"
#include "GameStateEnum.h"
#include "MainMenuScreen.h"

class Game
{
public:
	// Window size
	static const int WIDTH = 1024;
	static const int HEIGHT = 768;

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

