﻿#pragma once
#include "AbstractScreen.h"
#include "Scene.h"
#include "snake_part.h"
#include "snake.h"

class GameplayScreen
	:public AbstractScreen
{
public:
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void KeyboardButtonCallback(GLFWwindow* window, int button, int scancode, int action, int mods);
	GameplayScreen(GLFWwindow* window);
	void update();
	void render() override;
	void setBackgroundColor() override;

private:
	Scene scene;
	Snake * snake;
	SnakePart part;
	double fps;
	void FPSCounter();
};