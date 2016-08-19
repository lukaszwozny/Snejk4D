#include "GameplayScreen.h"

GameplayScreen::GameplayScreen(GLFWwindow* window)
	: AbstractScreen(window)
{
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
