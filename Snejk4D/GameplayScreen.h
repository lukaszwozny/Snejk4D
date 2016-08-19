#pragma once
#include "AbstractScreen.h"

class GameplayScreen
	:public AbstractScreen
{
public:
	GameplayScreen::GameplayScreen(GLFWwindow* window);

	void render() override;
	void setBackgroundColor() override;
};
