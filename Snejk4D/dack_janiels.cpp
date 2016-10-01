#include "dack_janiels.h"



DackJaniels::DackJaniels()
	:Food()
{
	type_ = FoodEnum::DACK_JANIELS;

	bottle = new Model("models/DJ_bottle.obj", "textures/DJ_bottle.bmp");
	label = new Model("models/DJ_label.obj", "textures/DJ_label.bmp");
	cork = new Model("models/DJ_cork.obj", "textures/DJ_cork.bmp");
}


DackJaniels::~DackJaniels()
{
	delete bottle;
	delete label;
	delete cork;
}

void DackJaniels::Display(glm::mat4 MVP)
{
	MVP = glm::translate(MVP, glm::vec3(0, 1.8f, 0));
	MVP = glm::translate(MVP, position_);
	bottle->Display(MVP);
	label->Display(MVP);
	cork->Display(MVP);
}
