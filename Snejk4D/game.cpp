#include "game.h"
#include <cstdio>
#include <ostream>
#include <iostream>

Game::Game()
{
	initGLFW();
}


Game::~Game()
{
}

int Game::Initialize()
{
	if (initGLFW() == -1)
		return -1;
	if (initGLFWwindow() == -1)
		return -1;
	return 0;
}

void Game::Start()
{
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	float color_red = 0;
	float color_green = 0;
	float color_blue = 0;
	bool more_red = true;
	bool more_green = true;
	bool more_blue = true;
	do
	{
		int random = rand() % 3;
		switch (random)
		{
		case 0:
			if (color_red > 1)
				more_red = false;
			if (color_red < 0)
				more_red = true;
			if (more_red)
				color_red += 0.01f;
			else
				color_red -= 0.01f;
			break;
		case 1:
			if (color_green > 1)
				more_green = false;
			if (color_green < 0)
				more_green = true;
			if (more_green)
				color_green += 0.01f;
			else
				color_green -= 0.01f;
			break;
		case 2:
			if (color_blue > 1)
				more_blue = false;
			if (color_blue < 0)
				more_blue = true;
			if (more_blue)
				color_blue += 0.01f;
			else
				color_blue -= 0.01f;
			break;
		}
		// Dark blue background
		glClearColor(color_red, color_green, color_blue, 0.0f);
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);


	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}

int Game::initGLFW()
{
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}
	return 0;
}

int Game::initGLFWwindow()
{
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 
	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1024, 768, "Tutorial 01", NULL, NULL);
	if (window == NULL)
	{
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // Initialize GLEW
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Set the mouse at the center of the screen
	glfwPollEvents();
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);
	return 0;
}
