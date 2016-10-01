#include "food.h"
#include "FileService.h"
#include "Scene.h"

Food::Food()
{
}

Food::~Food()
{
}


FoodEnum Food::getType() const
{
	return type_;
}
