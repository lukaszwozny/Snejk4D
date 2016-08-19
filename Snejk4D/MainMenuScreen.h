#pragma once
#include "gl_includes.h"
#include "GameStateEnum.h"
#include "AbstractScreen.h"

class MenuTextButton;

class MainMenuScreen
	: public AbstractScreen
{
public:
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	void initButtons();
	MainMenuScreen(GLFWwindow* window);
	void update() override;
//	void render();
private:
	MenuTextButton * new_game_on, *new_game_off;
	MenuTextButton * exit_game_on, *exit_game_off;

	static GameStateEnum getMouseState(GLFWwindow* window);
};
