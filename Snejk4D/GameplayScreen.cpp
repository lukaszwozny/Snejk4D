#include "GameplayScreen.h"
#include <iostream>

void GameplayScreen::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		std::cout << "LMB\n";
	}
}

GameplayScreen::GameplayScreen(GLFWwindow* window)
	: AbstractScreen(window)
{
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
}

void GameplayScreen::render()
{
	setBackgroundColor();
}

void GameplayScreen::setBackgroundColor()
{
	// Red background
	glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
