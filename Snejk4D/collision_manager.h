#pragma once
#include "snake.h"
#include "food.h"
#include "food_enum.h"
#include "FoodInfo.h"
#include "obstacle.h"

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void CheckFood(std::vector<FoodInfo*> & foods_);
	void CheckObstackle(std::vector<Obstacle*> & obstacle_vec);
	bool CheckTail();

	void setSnake(Snake* snake);

private:
	Snake * snake;
};

