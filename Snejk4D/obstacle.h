#pragma once
#include "gl_includes.h"
#include "obstacle_enum.h"

struct Obstacle
{
	Obstacle(ObstacleType type, int x, int z)
	{
		this->type = type;

		position.x = x;
		position.y = 0;
		position.z = z;
	}
	ObstacleType type;

	glm::vec3 position;
};
