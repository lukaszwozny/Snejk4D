#include "MainMenuScreen.h"
#include <iostream>


void MainMenuScreen::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		std::cout << "Click\n";
	}
}
