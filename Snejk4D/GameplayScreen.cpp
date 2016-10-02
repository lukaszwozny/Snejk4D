#include "GameplayScreen.h"
#include <iostream>
#include <string>

bool GameplayScreen::is_over = false;

void GameplayScreen::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		SoundService::Music();
		std::cout << "LMB click\n";
	}
}

int part_add_n = 0;

void GameplayScreen::KeyboardButtonCallback(GLFWwindow* window, int button, int scancode, int action, int mods)
{
	if (button == GLFW_KEY_KP_ADD && action == GLFW_PRESS)
	{
		part_add_n = 1;
	}
	if (button == GLFW_KEY_KP_SUBTRACT && action == GLFW_PRESS)
	{
		part_add_n = -1;
	}
}

GameplayScreen::GameplayScreen(GLFWwindow* window)
	: AbstractScreen(window)
{
	debug = true;

	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetKeyCallback(window, KeyboardButtonCallback);

	sound_service_ = new SoundService();
	control_service = new ControlService(window);

	LoadAll();
	collision_manager.setSnake(snake); //TODO change to pointer
	control_service->setSnake(snake);

	food_vec_.push_back(new FoodInfo(FoodEnum::COKE));
	food_vec_.push_back(new FoodInfo(FoodEnum::DACK_JANIELS));

	wall_part_ = new Model("models/cube.obj", "textures/scene_metal.bmp");
	scene_builder = new SceneBuilder();
	scene_builder->LoadMap(obstacle_vec_);
}

GameplayScreen::~GameplayScreen()
{
	delete control_service;
}

int rand_x = rand() % 60 - 30;
int rand_z = rand() % 60 - 30;

void GameplayScreen::update()
{
	FPSCounter();
	std::string title = "The Snejk 4D @ FPS: " + std::to_string(fps);
	glfwSetWindowTitle(window, title.c_str());

	if (!is_over)
		control_service->ComputeMatrixFromInput();
	glm::mat4 ProjectionMatrix = control_service->getProjectionMatrix();
	glm::mat4 ViewMatrix = control_service->getViewMatrix();
	glm::mat4 ModelMatrix = glm::mat4(1.0);
	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

	glm::vec3 test = glm::vec3(1, 1, 1);

	glm::mat4 tmp = glm::translate(MVP, glm::vec3(rand_x, 0, rand_z));
	DisplayFood(MVP);
	DisplayObstacle(MVP);

	if (!is_over)
		control_service->ComputeMoveMatrixFromInputs();
	scene.Display(MVP);
	snake->Display(MVP, control_service->getSnakePosition(), control_service->getRotateAngle());

	if (!is_over)
	{
		collision_manager.CheckFood(food_vec_);
		collision_manager.CheckObstackle(obstacle_vec_);
	}

	if (collision_manager.CheckTail())
	{
		// TODO Game Over
		std::cout << "Collison\n";
	}

	if (debug)
	{
		ChangeSnakeSize();
	}
}

void GameplayScreen::render()
{
	if (!is_over)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
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

void GameplayScreen::ChangeSnakeSize()
{
	switch (part_add_n)
	{
	case -1:
		snake->RemovePart();
		part_add_n = 0;
		break;
	case 1:
		snake->AddPart();
		part_add_n = 0;
		break;
	}
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

void GameplayScreen::LoadAll()
{
	snake = new Snake();
	coke = new Coke();
	dack_janiels = new DackJaniels();
}

void GameplayScreen::DisplayFood(glm::mat4 MVP)
{
	for (int i = 0; i < food_vec_.size(); ++i)
	{
		glm::mat4 temp = glm::translate(MVP, food_vec_[i]->position);
		switch (food_vec_[i]->type)
		{
		case COKE:
			coke->Display(temp);
			break;
		case DACK_JANIELS:
			dack_janiels->Display(temp);
			break;
		}
	}
}

void GameplayScreen::DisplayObstacle(glm::mat4 MVP)
{
	for (int i = 0; i < obstacle_vec_.size(); ++i)
	{
		glm::mat4 temp = glm::translate(MVP, obstacle_vec_[i]->position);
		switch (obstacle_vec_[i]->type)
		{
		case NONE:
			break;
		case WALL:
			wall_part_->Display(temp);
			break;
		}
	}
}
