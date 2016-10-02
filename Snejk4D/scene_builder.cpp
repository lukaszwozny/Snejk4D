#include "scene_builder.h"
#include "FileService.h"
#include <iostream>


SceneBuilder::SceneBuilder()
{
	FileService::LoadMap("maps/forest.txt", map_);
	std::cout << map_.width << "\n";
	std::cout << map_.height << "\n";

	for (int i = 0; i<map_.height; ++i)
	{
		for (int j = 0; j<map_.width; ++j)
		{
			std::cout << map_[i][j] << " ";
		}
		std::cout << "\n";
	}
}


SceneBuilder::~SceneBuilder()
{
}
