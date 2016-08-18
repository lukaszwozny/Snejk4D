#pragma once

//// Include GLEW
#include <GL/glew.h>

//// Include GLFW3
#include <glfw3.h>

//// Include GLM
#include <glm/glm.hpp>
#include "GameStateEnum.h"

class Game
{
public:
	static GameStateEnum game_state_enum;

	Game();
	~Game();
	int Initialize();
	void update();
	void Start();

private:
	GLFWwindow* window;

	int initGLFWwindow();
	int initGLFW();
};

