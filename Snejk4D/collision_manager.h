#pragma once
#include "snake.h"
#include "food.h"
#include "food_enum.h"
#include "FoodInfo.h"
#include "obstacle.h"
#include "scene_builder.h"

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void CheckFood(std::vector<FoodInfo*> & foods_, std::vector<Obstacle*>& obstacle_vec);
	void CheckObstackle(std::vector<Obstacle*> & obstacle_vec);
	void CheckTail();

	void setSnake(Snake* snake);

	void setSceneBuilder(SceneBuilder* scene_builder);
private:
	Snake * snake;
	SceneBuilder * scene_builder_;
};

