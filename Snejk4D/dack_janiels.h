#pragma once
#include "gl_includes.h"
#include "model.h"
#include "food.h"

class DackJaniels
	:public Food
{
public:
	DackJaniels();
	~DackJaniels();
	void Display(glm::mat4 MVP) override;
private:
	Model* bottle;
	Model* label;
	Model* cork;
};

