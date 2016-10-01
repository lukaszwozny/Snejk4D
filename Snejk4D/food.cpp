#include "food.h"
#include "FileService.h"

Food::Food()
{
}

Food::~Food()
{
}

glm::vec3 Food::position() const
{
	return position_;
}
