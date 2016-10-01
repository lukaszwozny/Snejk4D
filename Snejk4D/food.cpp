#include "food.h"
#include "FileService.h"
#include "Scene.h"

Food::Food()
{
	int pos_x = rand() % Scene::WIDTH - Scene::WIDTH/2;
	int pos_z = rand() % Scene::HEIGHT - Scene::HEIGHT/2;
	position_ = glm::vec3(pos_x, 0, pos_z);
}

Food::~Food()
{
}

void Food::setPosition(const glm::vec3& position)
{
	position_ = position;
}

glm::vec3 Food::getPosition() const
{
	return position_;
}

FoodEnum Food::getType() const
{
	return type_;
}
