#pragma once
#include "gl_includes.h"
#include <vector>

class Food
{
public:
	Food();
	~Food();
	virtual void Display(glm::mat4 MVP) = 0;
private:
};
