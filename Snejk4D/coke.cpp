#include "coke.h"


Coke::Coke()
	: Food()
{
	type_ = FoodEnum::COKE;

	can = new Model("models/coke_can.obj", "textures/coke_can.bmp");
	top = new Model("models/coke_top.obj", "textures/coke_top.bmp");
	bottom = new Model("models/coke_bottom.obj", "textures/coke_top.bmp");
}


Coke::~Coke()
{
	delete can;
	delete top;
	delete bottom;
}

void Coke::Display(glm::mat4 MVP)
{
	MVP = glm::translate(MVP, glm::vec3(0, -0.1, 0));
	can->Display(MVP);
	top->Display(MVP);
	bottom->Display(MVP);
}
