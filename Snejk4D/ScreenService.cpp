#include "ScreenService.h"
#include <iostream>
#include "MainMenuScreen.h"
#include "ScreenEnum.h"

ScreenService * instance = nullptr;

ScreenService * ScreenService::getInstance()
{
	if (instance == nullptr)
		instance = new ScreenService();
	return instance;
}

void ScreenService::SetScreen(GLFWwindow* window)
{
	ScreenEnum screen = ScreenEnum::MAiN_MENU;
	setActualScreenByEnum(window, screen);
	if (actual_screen != nullptr)
	{

		delete actual_screen;
	}

	actual_screen = new MainMenuScreen(window);
}

ScreenService::ScreenService()
{
	std::cout << "Create ScreenServce.";
}

void ScreenService::setActualScreenByEnum(GLFWwindow* window, ScreenEnum screen)
{
	switch (screen)
	{
	case ScreenEnum::MAiN_MENU: 
		actual_screen = new MainMenuScreen(window);
		break;
	case GAMEPLAY: 
		break;
	default: break;
	}
}
