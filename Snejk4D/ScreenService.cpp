#include "ScreenService.h"
#include <iostream>
#include "MainMenuScreen.h"
#include "ScreenEnum.h"
#include "GameplayScreen.h"

ScreenService * instance = nullptr;

ScreenService * ScreenService::getInstance()
{
	if (instance == nullptr)
		instance = new ScreenService();
	return instance;
}

void ScreenService::setScreen(GLFWwindow* window, ScreenEnum screen)
{
	if (actual_screen != nullptr)
		delete actual_screen;
	setActualScreenByEnum(window, screen);
}

AbstractScreen* ScreenService::getActualScreen() const
{
	return actual_screen;
}

void ScreenService::setActualScreenByEnum(GLFWwindow* window, ScreenEnum screen)
{
	switch (screen)
	{
	case ScreenEnum::MAiN_MENU: 
		actual_screen = new MainMenuScreen(window);
		break;
	case GAMEPLAY:
		actual_screen = new GameplayScreen(window);
		break;
	default: break;
	}
}
