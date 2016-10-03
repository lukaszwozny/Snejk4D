#include "GameplayScreen.h"
#include <iostream>
#include <string>
#include "game.h"

bool GameplayScreen::is_over = false;
int GameplayScreen::high_score = 0;

bool reset = false;
bool is_again = false;
bool is_menu = false;

void GameplayScreen::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		std::cout << "LMB click\n";
		if (is_again)
		{
			is_again = false;
			is_over = false;
			reset = true;
		}
		if (is_menu)
		{
			is_menu = false;
		}
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
	text_service = new Text2DService();

	LoadAll();
	collision_manager.setSnake(snake); //TODO change to pointer
	control_service->setSnake(snake);

	wall_part_ = new Model("models/cube.obj", "textures/scene_metal.bmp");
	scene_builder = new SceneBuilder(&obstacle_vec_, &food_vec_);
	scene_builder->LoadMap();
	collision_manager.setSceneBuilder(scene_builder);

	scene_builder->AddFood(FoodEnum::COKE);
	scene_builder->AddFood(FoodEnum::COKE);
	scene_builder->AddFood(FoodEnum::COKE);
	scene_builder->AddFood(FoodEnum::COKE);
	std::cout << food_vec_.size() << " size\n";
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
		collision_manager.CheckFood(food_vec_, obstacle_vec_);
		collision_manager.CheckObstackle(obstacle_vec_);
		collision_manager.CheckTail();
	}

	if (is_over)
	{
		char* game_over = "GAME OVER";
		int size = 80;
		int x_pos = Game::WIDTH / 2 - size * 6;
		int y_pos = Game::HEIGHT / 2;
		text_service->printText2D(game_over, x_pos, y_pos, size);

		// Again button
		double mouse_x, mouse_y;
		glfwGetCursorPos(window, &mouse_x, &mouse_y);

		// again? position
		float left = Game::WIDTH / 2 * 0.5f;
		float right = Game::WIDTH - 0.5f * 1024 / 2;
		float up = 768 / 2 + 20;
		float down = up - 51.0f;

		if (mouse_x > left && mouse_x < right
			&& mouse_y > down && mouse_y < up)
		{
			is_again = true;
			size = 80;
		}
		else
		{
			is_again = false;
			size = 50;
		}

		char* play_again = "again?";
		x_pos = Game::WIDTH / 2 - 140 - size * 3;
		y_pos = Game::HEIGHT / 2 - 100;
		text_service->printText2D(play_again, x_pos, y_pos, size);

		// Back to menu button
		// again? position
		size = 30;
		if (snake->getSize() - 7 > high_score)
			high_score = snake->getSize() - 7;
		std::string high_score_text = "High score: " + std::to_string(high_score);
		x_pos = 0;
		y_pos = 0;
		text_service->printText2D(high_score_text.c_str(), x_pos, y_pos, size);
	}

	if (reset)
	{
		control_service->setSnakePosition(glm::vec3(0, 0, 0));
		control_service->SetRotateSnakeAngle(0.0f);
		snake->Reset();
		reset = false;
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

	std::string fps_s = std::to_string(int(fps)) + " fps";
	text_service->printText2D(fps_s.c_str(), 0, 550, 30);

	std::string score = "Score: " + std::to_string(snake->getSize() - 7);
	text_service->printText2D(score.c_str(), 370, 550, 40);
}

void GameplayScreen::LoadAll()
{
	SoundService::Music();
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
