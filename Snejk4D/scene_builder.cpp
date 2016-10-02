#include "scene_builder.h"
#include "FileService.h"
#include <iostream>


SceneBuilder::SceneBuilder()
{
}


SceneBuilder::~SceneBuilder()
{
}

void SceneBuilder::Build()
{
}

void SceneBuilder::LoadMap(std::vector<Obstacle*>& obstacle_vec)
{
	FileService::LoadMap("maps/forest.txt", map_);
	std::cout << map_.width << "\n";
	std::cout << map_.height << "\n";

	const int OFFSET_X = map_.width / 2;
	const int OFFSET_Y = map_.height / 2;
	const float INTERVAL = 2.0f;

	for (int i = 0; i < map_.height; ++i)
	{
		for (int j = 0; j < map_.width; ++j)
		{
			ObstacleType tmp = ObstacleType(map_[i][j]);
			obstacle_vec.push_back(new Obstacle(tmp, j * INTERVAL - OFFSET_X, i * INTERVAL - OFFSET_Y));
		}
		std::cout << "\n";
	}
}
