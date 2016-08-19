#include "Scene.h"

void Scene::Display(glm::mat4 MVP)
{
	for (int i = -100; i < 100; i += 4)
	{
		for (int j = -100; j < 100; j += 4)
		{
			//MVP = glm::translate(MVP, glm::vec3(i, j, 0));
			scene_part.Display(glm::translate(MVP, glm::vec3(i, 0, j)));
		}
	}
}
