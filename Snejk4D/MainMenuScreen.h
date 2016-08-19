#pragma once
#include "gl_includes.h"
#include "GameStateEnum.h"

class MenuTextButton;

class MainMenuScreen
{
public:
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	void initButtons();
	MainMenuScreen(GLFWwindow* window);
	void update();
	void render();
private:
	GLFWwindow* window;
	MenuTextButton * new_game_on, *new_game_off;
	MenuTextButton * exit_game_on, *exit_game_off;

	static GameStateEnum getMouseState(GLFWwindow* window);
};
