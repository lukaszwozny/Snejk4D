#include "ControlService.h"
#include <ios>
#include <iostream>

ControlService::ControlService(GLFWwindow* window)
{
	window_ = window;

	lastTime = glfwGetTime();
	camera_state_ = CameraStateEnum::ON_SNAKE_VIEW;
}

void ControlService::ComputeMatrixFromInput()
{
	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();
	static float x = 0.0;
	static float z = 0.0;
	static float angle = 0.0;

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window_, &xpos, &ypos);

	// Reset mouse position for next frame
	glfwSetCursorPos(window_, 1024 / 2, 768 / 2);


	glm::vec3 move_direction(
		cos(angle),
		0,
		sin(angle)
	);
	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	// Right vector
	glm::vec3 up2 = glm::vec3(
		0,
		camera_speed,
		0
	);
	// Up vector
	glm::vec3 up = glm::cross(right, direction);

	switch (camera_state_)
	{
	case CLASSIC_VIEW:
		horizontalAngle = -4.70501f;
		verticalAngle = -1.365f;
		position = glm::vec3(0, 81, 27);
		break;
	case AERIAL_VIEW:
		horizontalAngle = -4.48501f;
		verticalAngle = -0.675f;
		position = glm::vec3(-16, 20, 22);
		break;
	case ON_SNAKE_VIEW:
		if (snake->getAngleBuffers()[0]->size() > 0)
			horizontalAngle = snake->getAngleBuffers()[0]->front();
		verticalAngle = -0.2f;
		if (snake->getPositionBuffers()[0]->size() > 3)
			position = snake->getPositionBuffers()[3]->front() + glm::vec3(0, 2.5, 0);
		break;
	case FREE_VIEW:
		horizontalAngle += mouseSpeed * float(1024 / 2 - xpos);
		verticalAngle += mouseSpeed * float(768 / 2 - ypos);

		// Move forward
		if (glfwGetKey(window_, GLFW_KEY_UP) == GLFW_PRESS)
		{
			position += direction * deltaTime * camera_speed;
		}
		// Move backward
		if (glfwGetKey(window_, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			position -= direction * deltaTime * camera_speed;
		}
		// Strafe right
		if (glfwGetKey(window_, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			position += right * deltaTime * camera_speed;
		}
		// Strafe left
		if (glfwGetKey(window_, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			position -= right * deltaTime * camera_speed;
		}
		// Strafe up
		if (glfwGetKey(window_, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			position += up2 * deltaTime * camera_speed;
		}
		// Strafe down
		if (glfwGetKey(window_, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			position -= up2 * deltaTime * camera_speed;
		}

		break;
	}

	glm::mat4 move_tmp = glm::mat4(1.0);
	// Move forward
	if (glfwGetKey(window_, GLFW_KEY_W) == GLFW_PRESS)
	{
		z -= 0.005;
		move_tmp = glm::translate(glm::mat4(1.0), glm::vec3(z * deltaTime * cos(angle), 0, z * deltaTime * sin(angle)));
	}
	// Move backward
	if (glfwGetKey(window_, GLFW_KEY_S) == GLFW_PRESS)
	{
		z = 0.0;
		angle = 0.0;
		move_tmp = glm::translate(glm::mat4(1.0), glm::vec3(z * cos(angle), 0, z * sin(angle)));
		move_tmp = glm::rotate(move_tmp, angle, glm::vec3(0, 1, 0));
	}
	// Strafe right
	if (glfwGetKey(window_, GLFW_KEY_D) == GLFW_PRESS)
	{
		angle = -deltaTime;
		move_tmp = glm::rotate(move_tmp, angle, glm::vec3(0, 1, 0));
	}
	// Strafe left
	if (glfwGetKey(window_, GLFW_KEY_A) == GLFW_PRESS)
	{
		angle = deltaTime;
		move_tmp = glm::rotate(move_tmp, angle, glm::vec3(0, 1, 0));
	}


	float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.


	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	ViewMatrix = glm::lookAt(
		position, // Camera is here
		position + direction, // and looks here : at the same position, plus "direction"
		up // Head is up (set to 0,-1,0 to look upside-down)
	);
	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}

void ControlService::ComputeMoveMatrixFromInputs()
{
	static double movelastTime = glfwGetTime();
	static double rotatelastTime = glfwGetTime();

	double currentTime = glfwGetTime();
	float movedeltaTime = float(currentTime - movelastTime);
	float rotatedeltaTime = float(currentTime - rotatelastTime);

	glm::vec3 move_direction(
		sin(rotate_snake_angle),
		0,
		cos(rotate_snake_angle)
	);

	//always go on
	if (movedeltaTime > 0.01f)
	{
		snake_position += 0.02f * move_direction * move_snake_speed;
		movelastTime = currentTime;
	}
	// Move backward
	if (glfwGetKey(window_, GLFW_KEY_S) == GLFW_PRESS)
	{
		/*if (movedeltaTime > 0.02) {
		snake_position -= move_direction*0.05f;
		movedeltaTime = currentTime;
		}*/
	}
	// Strafe right
	if (glfwGetKey(window_, GLFW_KEY_D) == GLFW_PRESS)
	{
		if (rotatelastTime > 1.0f / 60.0f)
		{
			rotate_snake_angle -= /* dizzy* */rotate_snake_speed;
			rotatelastTime = currentTime;
		}
	}
	// Strafe left
	if (glfwGetKey(window_, GLFW_KEY_A) == GLFW_PRESS)
	{
		if (rotatelastTime > 1.0f / 60.0f)
		{
			rotate_snake_angle += /* dizzy* */rotate_snake_speed;
			rotatelastTime = currentTime;
		}
	}

	MovewMatrix = glm::translate(glm::mat4(1.0), snake_position);
	MovewMatrix = glm::rotate(MovewMatrix, rotate_snake_angle, glm::vec3(0, 1, 0));
}

/*
	Getters and setters
*/


glm::mat4 ControlService::getViewMatrix()
{
	return ViewMatrix;
}

glm::mat4 ControlService::getProjectionMatrix()
{
	return ProjectionMatrix;
}

glm::mat4 ControlService::getMoveMatrix()
{
	return MovewMatrix;
}

glm::vec3 ControlService::getSnakePosition()
{
	return snake_position;
}

float ControlService::getRotateAngle()
{
	return rotate_snake_angle;
}

void ControlService::setSnakePosition(const glm::vec3& snake_position)
{
	this->snake_position = snake_position;
}

void ControlService::SetRotateSnakeAngle(float rotate_snake_angle)
{
	this->rotate_snake_angle = rotate_snake_angle;
}

void ControlService::setSnake(Snake* snake)
{
	this->snake = snake;
}
