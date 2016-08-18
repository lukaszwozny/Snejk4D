#pragma once

//// Include GLEW
#include <GL/glew.h>

//// Include GLFW3
#include <glfw3.h>

//// Include GLM
#include <glm/glm.hpp>

class Game
{
public:
	Game();
	~Game();
	int Initialize();
	void Start();

private:
	GLFWwindow* window;

	int initGLFWwindow();
	int initGLFW();
};

