#include "scene_builder.h"
#include "FileService.h"
#include <iostream>

int SceneBuilder::WIDTH = 0;
int SceneBuilder::HEIGHT = 0;
int SceneBuilder::START_X = 0;
int SceneBuilder::START_Y = 0;


SceneBuilder::SceneBuilder(std::vector<Obstacle*>* obstacle_vec, std::vector<FoodInfo*>* food_vec)
{
	obstacle_vec_ = obstacle_vec;
	food_vec_ = food_vec;
}

SceneBuilder::~SceneBuilder()
{
}

void SceneBuilder::Build()
{
}

void SceneBuilder::AddFood(FoodEnum type)
{
	FoodInfo* tmp = nullptr;
	bool ok_food = false;
	while (!ok_food)
	{
		int pos_x = rand() % (WIDTH - 2) + START_X + 1;
		int pos_z = rand() % (HEIGHT - 2) + START_Y + 1;

		tmp = new FoodInfo(type);
		tmp->position = glm::vec3(pos_x, 0, pos_z);

		if (CheckNewFood(tmp))
		{
			ok_food = true;
		}
		else
		{
			delete tmp;
		}
	}
	food_vec_->push_back(tmp);
}

void SceneBuilder::LoadMap()
{
	FileService::LoadMap("maps/forest.txt", map_);

	const int OFFSET_X = map_.width / 2;
	const int OFFSET_Y = map_.height / 2;
	const float INTERVAL = 2.0f;

	for (int i = 0; i < map_.height; ++i)
	{
		for (int j = 0; j < map_.width; ++j)
		{
			ObstacleType tmp = ObstacleType(map_[i][j]);
			obstacle_vec_->push_back(new Obstacle(tmp, j * INTERVAL - OFFSET_X, i * INTERVAL - OFFSET_Y));
		}
		std::cout << "\n";
	}

	WIDTH = map_.width * INTERVAL;
	HEIGHT = map_.height * INTERVAL;
	START_X = -OFFSET_X;
	START_Y = -OFFSET_Y;
}

bool SceneBuilder::CheckNewFood(FoodInfo* food)
{
	for (int i = 0; i < obstacle_vec_->size(); ++i)
	{
		if (obstacle_vec_->at(i)->type != ObstacleType::NONE)
		{
			float obst_x = obstacle_vec_->at(i)->position.x;
			float obst_z = obstacle_vec_->at(i)->position.z;
			const float RADIUS = 3;
			if (!(abs(food->position.x - obst_x) > RADIUS || abs(food->position.z - obst_z) > RADIUS))
			{
				return false;
			}
		}
	}
	return true;
}
