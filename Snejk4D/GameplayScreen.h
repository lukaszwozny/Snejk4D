#pragma once
#include "AbstractScreen.h"
#include "Scene.h"
#include "snake_part.h"
#include "snake.h"
#include "coke.h"
#include "dack_janiels.h"
#include "collision_manager.h"

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

	// debug
	void ChangeSnakeSize();

private:
	bool debug;

	CollisionManager collision_manager;

	Scene scene;
	Snake * snake;

	Coke * coke;
	DackJaniels * dack_janiels;

	double fps;
	void FPSCounter();
};
