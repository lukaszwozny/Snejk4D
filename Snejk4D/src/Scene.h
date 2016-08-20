#pragma once
#include "gl_includes.h"
#include "ScenePart.h"

class Scene
{
public:
	void Display(glm::mat4 MVP);

private:
	ScenePart scene_part;
	glm::mat4 MVP;
};
