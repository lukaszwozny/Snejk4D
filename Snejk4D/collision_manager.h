#pragma once
#include "snake.h"

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void ChaeckFood(int foodX, int foodZ);
	bool CheckTail();

	void setSnake(Snake* snake);

private:
	Snake * snake;
};

