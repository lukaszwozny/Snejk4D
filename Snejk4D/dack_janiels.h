#pragma once
#include "gl_includes.h"
#include "model.h"

class DackJaniels
{
public:
	DackJaniels();
	~DackJaniels();
	void Display(glm::mat4 MVP);
private:
	Model* bottle;
	Model* label;
	Model* cork;
};

