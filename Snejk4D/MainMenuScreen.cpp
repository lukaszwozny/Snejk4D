#pragma once
#include <iostream>

#include "MainMenuScreen.h"
#include "MenuTextButton.h"


void MainMenuScreen::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		std::cout << getMouseState(window);
	}
}

void MainMenuScreen::initButtons()
{
	new_game_on = new MenuTextButton("textures/new_game_on.bmp");
}

GameStateEnum MainMenuScreen::getMouseState(GLFWwindow* window)
{
	double mouse_x, mouse_y;
	glfwGetCursorPos(window, &mouse_x, &mouse_y);

	//render Game
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


MainMenuScreen::MainMenuScreen(GLFWwindow* window)
{
	this->window = window;
	glfwSetMouseButtonCallback(window, MouseButtonCallback);

	initButtons();
}

void MainMenuScreen::update()
{

}

void MainMenuScreen::render()
{
	MenuTextButton test = MenuTextButton("");
	do
	{
		// Dark blue background
		glClearColor(0.0f, 0.6f, 0.6f, 0.0f);
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//		update();
		test.Display(glm::vec3(0, 0.4, 0));

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
}
