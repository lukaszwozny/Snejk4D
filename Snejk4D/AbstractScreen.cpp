#include "AbstractScreen.h"
#include <GL/glew.h>
#include <glfw3.h>

AbstractScreen::AbstractScreen(GLFWwindow* window)
{
	this->window = window;
}

void AbstractScreen::setBackgroundColor()
{
	// Pink background
	glClearColor(1.0f, 0.8f, 0.8f, 0.0f);
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
