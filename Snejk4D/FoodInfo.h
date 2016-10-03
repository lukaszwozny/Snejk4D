#pragma once
#include "gl_includes.h"
#include "Scene.h"
#include "food_enum.h"

struct FoodInfo
{
	FoodInfo(FoodEnum type)
	{
		this->type = type;

		position = glm::vec3(0, 0, 0);
	}

	FoodInfo()
	{
		type = FoodEnum(rand() % 2);

		int pos_x = 0;
		int pos_z = 0;
		position = glm::vec3(pos_x, 0, pos_z);
	}
	FoodEnum type;

	glm::vec3 position;
};
