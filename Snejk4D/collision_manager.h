#pragma once
#include "snake.h"
#include "food.h"
#include "food_enum.h"
#include "FoodInfo.h"

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void ChaeckFood(std::vector<FoodInfo*> & foods_);
	bool CheckTail();

	void setSnake(Snake* snake);

private:
	Snake * snake;
};

