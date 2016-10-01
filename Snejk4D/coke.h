#pragma once
#include "model.h"
#include "food.h"

class Coke
	:public Food
{
public:
	Coke();
	~Coke();
	void Display(glm::mat4 MVP) override;
private:
	Model* can;
	Model* top;
	Model* bottom;
};

