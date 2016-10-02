#pragma once
#include <vector>
#include "map.h"
#include "obstacle.h"

class SceneBuilder
{
public:
	SceneBuilder();
	~SceneBuilder();
	void Build();
	void LoadMap(std::vector<Obstacle*>& obstacle_vec);
private:
	Map map_;
};

