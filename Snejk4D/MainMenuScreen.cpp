#include "MainMenuScreen.h"
#include <iostream>


void MainMenuScreen::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		std::cout << getMouseState(window);
	}
}

GameStateEnum MainMenuScreen::getMouseState(GLFWwindow* window)
{
	double mouse_x, mouse_y;
	glfwGetCursorPos(window, &mouse_x, &mouse_y);

	//Start Game
	int left = 1024 / 2 * 0.5f;
	int right = 1024 - 0.5f * 1024 / 2;
	int up = (1.0f - 0.4f) * 768 / 2 + 51.0f / 2.0f;
	int down = (1.0f - 0.4f) * 768 / 2 - 51.0f / 2.0f;

	if (mouse_x > left && mouse_x < right
		&& mouse_y > down && mouse_y < up) {
		return PLAY_GAME;
	}

	//End Game
	left = 1024 / 2 - 100.0f;
	right = 1024 / 2 + 100.0f;
	up = (1.0f + 0.4f) * 768 / 2 + 51.0f / 2.0f;
	down = (1.0f + 0.4f) * 768 / 2 - 51.0f / 2.0f;

	if (mouse_x > left && mouse_x < right
		&& mouse_y > down && mouse_y < up) {
		return EXIT;
	}

	return MENU;
}
