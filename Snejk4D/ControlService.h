#pragma once
#include "gl_includes.h"

class ControlService
{
public:
	ControlService(GLFWwindow* window);
	void ComputeMatrixFromInput();
	void ComputeMoveMatrixFromInputs();

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	glm::mat4 getMoveMatrix();

	glm::vec3 getSnakePosition();
	float getRotateAngle();

private:
	GLFWwindow* window_;

	glm::mat4 MovewMatrix;
	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;

	// Initial getPosition : on +Z
	glm::vec3 position = glm::vec3(0, 0, 5);
	// Initial horizontal angle : toward -Z
	float horizontalAngle = 3.14f;
	// Initial vertical angle : none
	float verticalAngle = 0.0f;
	// Initial Field of View
	float initialFoV = 45.0f;
	// initial snake positon
	glm::vec3 snake_position = glm::vec3(0, 0, 0);

	float camera_speed = 3.0f; // 3 units / second
	float mouseSpeed = 0.005f;

	float move_snake_speed = 10.0f; // 3 units / second
	float rotate_snake_angle = 0.0;
	float rotate_snake_speed = move_snake_speed*0.002f;
};
