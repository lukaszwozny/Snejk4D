#pragma once
#include "gl_includes.h"

class ControlService
{
public:
	ControlService(GLFWwindow* window);
	void ComputeMatrixFromInput();

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	glm::mat4 getMoveMatrix();

private:
	GLFWwindow* window_;

	glm::mat4 MovewMatrix;
	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;

	// Initial position : on +Z
	glm::vec3 position = glm::vec3(0, 0, 5);
	// Initial horizontal angle : toward -Z
	float horizontalAngle = 3.14f;
	// Initial vertical angle : none
	float verticalAngle = 0.0f;
	// Initial Field of View
	float initialFoV = 45.0f;

	float camera_speed = 3.0f; // 3 units / second
	float mouseSpeed = 0.005f;
};
