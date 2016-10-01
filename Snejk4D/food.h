#pragma once
#include "gl_includes.h"
#include <vector>
#include "food_enum.h"

class Food
{
public:
	Food();
	~Food();
	virtual void Display(glm::mat4 MVP) = 0;

	FoodEnum getType() const;
protected:
	FoodEnum type_;
};
