#pragma once
#include "model.h"

class Coke
{
public:
	Coke();
	~Coke();
	void Display(glm::mat4 MVP);
private:
	Model* can;
	Model* top;
	Model* bottom;
};

