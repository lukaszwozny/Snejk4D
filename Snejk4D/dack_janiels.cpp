#include "dack_janiels.h"



DackJaniels::DackJaniels()
{
	bottle = new Food("models/DJ_bottle.obj", "textures/DJ_bottle.bmp");
	label = new Food("models/DJ_label.obj", "textures/DJ_label.bmp");
	cork = new Food("models/DJ_cork.obj", "textures/DJ_label.bmp");
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
	bottle->Display(MVP);
	label->Display(MVP);
	cork->Display(MVP);
}
