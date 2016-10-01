#pragma once
#include "food.h"

class Coke
{
public:
	Coke();
	~Coke();
	void Display(glm::mat4 MVP);
private:
	Food* can;
	Food* top;
	Food* bottom;
};

