#include "collision_manager.h"
#include <iostream>


CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::CheckFood(std::vector<FoodInfo*>& foods_)
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
			foods_.push_back(new FoodInfo(foods_[i]->type));

			delete foods_[i];
			foods_.erase(foods_.begin() + i);

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
				std::cout << "Bum :(\n";
			}
		}
	}

}

bool CollisionManager::CheckTail()
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


		for (int i = 15; i < snake->getSize(); ++i)
		{
			glm::vec3 old_pos;
			old_pos = position_buffers[i]->front();
			if (!(abs(head_xpos - old_pos.x) > 2 || abs(head_zpos - old_pos.z) > 2))
				return true;
		}
	}
	return false;
}

void CollisionManager::setSnake(Snake* snake)
{
	this->snake = snake;
}
