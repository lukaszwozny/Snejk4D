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
#include "scene_builder.h"
#include "sound_service.h"

class GameplayScreen
	:public AbstractScreen
{
public:
	static bool is_over;
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

	SoundService * sound_service_;
	ControlService * control_service;
	CollisionManager collision_manager;
	SceneBuilder * scene_builder;

	Scene scene;

	// Models
	Snake * snake;
	Model * wall_part_;
	Coke * coke;
	DackJaniels * dack_janiels;

	std::vector<FoodInfo*> food_vec_;
	std::vector<Obstacle*> obstacle_vec_;

	double fps;
	void FPSCounter();

	void LoadAll();
	void DisplayFood(glm::mat4 MVP);
	void DisplayObstacle(glm::mat4 MVP);
};
