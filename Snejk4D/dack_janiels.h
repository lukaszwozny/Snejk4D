#pragma once
#include "gl_includes.h"
#include "food.h"

class DackJaniels
{
public:
	DackJaniels();
	~DackJaniels();
	void Display(glm::mat4 MVP);
private:
	Food* bottle;
	Food* label;
	Food* cork;
};

