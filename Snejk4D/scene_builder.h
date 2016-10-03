#pragma once
#include <vector>
#include "map.h"
#include "obstacle.h"
#include "food_enum.h"
#include "FoodInfo.h"

class SceneBuilder
{
public:
	static int WIDTH;
	static int HEIGHT;
	static int START_X;
	static int START_Y;

	SceneBuilder(std::vector<Obstacle*>* obstacle_vec, std::vector<FoodInfo*>* food_vec);
	~SceneBuilder();
	void Build();
	void AddFood(FoodEnum type);
	void LoadMap();
private:
	Map map_;
	std::vector<Obstacle*>* obstacle_vec_;
	std::vector<FoodInfo*>* food_vec_;

	bool CheckNewFood(FoodInfo * food);
};

