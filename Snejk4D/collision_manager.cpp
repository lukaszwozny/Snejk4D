#include "collision_manager.h"
#include <iostream>
#include "GameplayScreen.h"


CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::CheckFood(std::vector<FoodInfo*>& foods_, std::vector<Obstacle*>& obstacle_vec)
{
	float head_xpos = 0;
	float head_zpos = 0;
	static bool first = true;

	std::vector<std::queue<glm::vec3>*> position_buffers;

	position_buffers = snake->getPositionBuffers();
	glm::vec3 pos_test;
	pos_test = position_buffers[0]->front();

	head_xpos = pos_test.x;
	head_zpos = pos_test.z;

	for(int i=0; i< foods_.size(); ++i)
	{
		float food_x = foods_[i]->position.x;
		float food_z = foods_[i]->position.z;
		if (!(abs(head_xpos - food_x) > 2 || abs(head_zpos - food_z) > 2))
		{
			switch (foods_[i]->type)
			{
			case COKE:
				snake->AddPart();
				break;
			case DACK_JANIELS:
				break;
			}
			delete foods_[i];
			foods_.erase(foods_.begin() + i);
			scene_builder_->AddFood(FoodEnum::COKE);
		}
	}
}

void CollisionManager::CheckObstackle(std::vector<Obstacle*>& obstacle_vec)
{
	float head_xpos = 0;
	float head_zpos = 0;
	static bool first = true;

	std::vector<std::queue<glm::vec3>*> position_buffers;

	position_buffers = snake->getPositionBuffers();
	glm::vec3 pos_test;
	pos_test = position_buffers[0]->front();

	head_xpos = pos_test.x;
	head_zpos = pos_test.z;

	for (int i = 0; i< obstacle_vec.size(); ++i)
	{
		if(obstacle_vec[i]->type != ObstacleType::NONE)
		{
			float x_pos = obstacle_vec[i]->position.x;
			float z_pos = obstacle_vec[i]->position.z;
			if (!(abs(head_xpos - x_pos) > 2 || abs(head_zpos - z_pos) > 2))
			{
				GameplayScreen::is_over = true;
				// TODO handle collision
			}
		}
	}

}

void CollisionManager::CheckTail()
{
	static double lastTime = glfwGetTime();
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	float head_xpos = 0;
	float head_zpos = 0;
	static bool first = true;

	std::vector < std::queue <glm::vec3>* > position_buffers;
	if (first && (deltaTime > 3)) {
		first = false;
		lastTime = currentTime;
	}
	if (!first)
	{
		position_buffers = snake->getPositionBuffers();
		glm::vec3 pos_test;
		pos_test = position_buffers[0]->front();

		head_xpos = pos_test.x;
		head_zpos = pos_test.z;


		for (int i = 15; i < snake->getSize()-1; ++i)
		{
			glm::vec3 old_pos;
			old_pos = position_buffers[i]->front();
			const float RADIUS = 2.0f;
			if (!(abs(head_xpos - old_pos.x) > RADIUS || abs(head_zpos - old_pos.z) > RADIUS))
			{
				GameplayScreen::is_over = true;
				return;
			}
		}
	}
}

void CollisionManager::setSnake(Snake* snake)
{
	this->snake = snake;
}

void CollisionManager::setSceneBuilder(SceneBuilder* scene_builder)
{
	scene_builder_ = scene_builder;
}
