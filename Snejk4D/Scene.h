#pragma once
#include "gl_includes.h"
#include "ScenePart.h"

class Scene
{
public:
	static const int WIDTH = 60;
	static const int HEIGHT = 60;

	void Display(glm::mat4 MVP);

private:
	ScenePart scene_part;
	glm::mat4 MVP;
};
