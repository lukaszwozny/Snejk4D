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
//	glfwSetMouseButtonCallback(window, MouseButtonCallback);

	glfwSetMouseButtonCallback(window, MouseButtonCallback);

	snake = new Snake();
	snake->AddPart();
	snake->AddPart();
	snake->AddPart();
	snake->AddPart();
	snake->AddPart();
	snake->AddPart();
	snake->AddPart();
	snake->AddPart();
	snake->AddPart();
	snake->AddPart();
}

void GameplayScreen::update()
{
	FPSCounter();
	std::string title = "The Snejk 4D @ FPS: " + std::to_string(fps);
	glfwSetWindowTitle(window, title.c_str());

	computeMatricesFromInputs(window);
	moveMatrixFromInputs(window);
	glm::mat4 ProjectionMatrix = getProjectionMatrix();
	glm::mat4 ViewMatrix = getViewMatrix();
	glm::mat4 ModelMatrix = glm::mat4(1.0);
	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

	glm::vec3 test = glm::vec3(1, 1, 1);

	scene.Display(MVP);
//	part.Display(MVP);
	snake->Display(MVP, getSnakePosition(), getRotateAngle());
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

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);
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
