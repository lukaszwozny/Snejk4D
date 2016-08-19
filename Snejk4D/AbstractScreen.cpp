#include "AbstractScreen.h"
#include <GL/glew.h>
#include <glfw3.h>

AbstractScreen::AbstractScreen(GLFWwindow* window)
{
	this->window = window;
	is_end = false;
}

void AbstractScreen::render()
{
	do
	{
		// Black background
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		update();

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0 &&
		is_end == false);
}

void AbstractScreen::end()
{
	is_end = true;
}
