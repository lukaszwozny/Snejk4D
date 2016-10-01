#pragma once
#include "snake.h"

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void Chaeck(int foodX, int foodZ);
	bool CheckTail();

	void setSnake(Snake* snake);

private:
	Snake * snake;
};

