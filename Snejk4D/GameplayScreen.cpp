#include "GameplayScreen.h"
#include <iostream>
#include <string>
#include "controls.hpp"

void GameplayScreen::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		std::cout << "LMB click\n";
	}
}

GameplayScreen::GameplayScreen(GLFWwindow* window)
	: AbstractScreen(window)
{
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
}

void GameplayScreen::update()
{
	FPSCounter();
	std::string title = "The Snejk 4D @ FPS: " + std::to_string(fps);
	glfwSetWindowTitle(window, title.c_str());

	computeMatricesFromInputs(window);
	moveMatrixFromInputs();
	glm::mat4 ProjectionMatrix = getProjectionMatrix();
	glm::mat4 ViewMatrix = getViewMatrix();
	glm::mat4 ModelMatrix = glm::mat4(1.0);
	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

	scene.Display(MVP);
}

void GameplayScreen::render()
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	setBackgroundColor();
	update();
}

void GameplayScreen::setBackgroundColor()
{
	// Red background
	glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GameplayScreen::FPSCounter()
{
	static double prev_time = glfwGetTime();
	double actual_time = glfwGetTime();

	static int frames_counter = 0;

	double elapsed_time = actual_time - prev_time;
	if (elapsed_time >= 1.0)
	{
		prev_time = actual_time;

		fps = static_cast<double>(frames_counter) / elapsed_time;
		frames_counter = 0;
	}

	frames_counter++;
}
