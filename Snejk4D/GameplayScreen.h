#pragma once
#include <vector>
#include "AbstractScreen.h"
#include "Scene.h"
#include "snake_part.h"
#include "snake.h"
#include "coke.h"
#include "dack_janiels.h"
#include "food.h"
#include "collision_manager.h"
#include "ControlService.h"
#include "FoodInfo.h"

class GameplayScreen
	:public AbstractScreen
{
public:
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void KeyboardButtonCallback(GLFWwindow* window, int button, int scancode, int action, int mods);
	GameplayScreen(GLFWwindow* window);
	~GameplayScreen();
	void update();
	void render() override;
	void setBackgroundColor() override;

	// debug
	void ChangeSnakeSize();

private:
	bool debug;

	ControlService * control_service;
	CollisionManager collision_manager;

	Scene scene;

	// Models
	Snake * snake;
	Coke * coke;
	DackJaniels * dack_janiels;

	std::vector<FoodInfo*> food_vec_;

	double fps;
	void FPSCounter();

	void LoadAll();
	void DisplayFood(glm::mat4 MVP);
};
