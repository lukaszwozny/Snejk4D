#pragma once
#include "gl_includes.h"

class ControlService
{
public:
	void ComputeMatrixFromInput();

	glm::mat4 getViewMatrix();
	glm::mat4 getMoveMatrix();

	glm::mat4 MovewMatrix;
	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;

private:
	GLFWwindow* window;
};
