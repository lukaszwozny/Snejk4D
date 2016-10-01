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

	void setPosition(const glm::vec3& position);
	glm::vec3 getPosition() const;

	FoodEnum getType() const;
protected:
	glm::vec3 position_;
	FoodEnum type_;
};
