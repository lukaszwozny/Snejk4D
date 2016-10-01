#pragma once
#include "gl_includes.h"
#include "Scene.h"
#include "food_enum.h"

struct FoodInfo
{
	FoodInfo(FoodEnum type)
	{
		this->type = type;

		int pos_x = rand() % Scene::WIDTH - Scene::WIDTH / 2;
		int pos_z = rand() % Scene::HEIGHT - Scene::HEIGHT / 2;
		position = glm::vec3(pos_x, 0, pos_z);
	}

	FoodInfo()
	{
		type = FoodEnum(rand() % 2);

		int pos_x = rand() % Scene::WIDTH - Scene::WIDTH / 2;
		int pos_z = rand() % Scene::HEIGHT - Scene::HEIGHT / 2;
		position = glm::vec3(pos_x, 0, pos_z);
	}
	FoodEnum type;

	glm::vec3 position;
};
