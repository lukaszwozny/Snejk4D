// Include GLFW
#include <cstdlib>

#include "gl_includes.h"
#include "GameStateEnum.h"
#include "CameraStateEnum.h"
 GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

						   // Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "controls.hpp"

glm::mat4 ViewMatrix;
glm::mat4 MovewMatrix;
glm::mat4 ProjectionMatrix;
int snake_size = 4;
int r_x = 0;
int r_z = 0;
glm::vec3 camera_on_snake_position;
float camera_on_snake_angle;



glm::mat4 getViewMatrix() {
	return ViewMatrix;
}
glm::mat4 getMoveMatrix() {
	return MovewMatrix;
}
int getSizeOfSnake()
{
	return snake_size;
}

glm::mat4 getProjectionMatrix() {
	return ProjectionMatrix;
}


// Initial position : on +Z
glm::vec3 position = glm::vec3(0, 0, 5);
glm::vec3 snake_position = glm::vec3(0, 0, 0);
// Initial horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 10.0f; // 3 units / second
float move_snake_speed = 10.0f; // 3 units / second
float rotate_snake_angle = 0.0;
float rotate_snake_speed = move_snake_speed*0.002f;
float mouseSpeed = 0.005f;
int dizzy = 1;

GameStateEnum menu_state = MENU;
GameStateEnum game_state = MENU;
CameraStateEnum camera_state = ON_SNAKE_VIEW;

//Snake* snake_ptr;
//
//void setSnakePtr(Snake * snake)
//{
//	snake_ptr = snake;
//}

int getDizzyState()
{
	return dizzy;
}

void setDizzyState(int state)
{
	dizzy = state;
}

float getSnakeSpeed() {
	return move_snake_speed;
}

void getRandomFood(int & rand_x, int & rand_z)
{
	static double lastTime = glfwGetTime();
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);
	//add part
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		if (deltaTime > 0.2) {
			rand_x = rand() % 60 - 30;
			rand_z = rand() % 60 - 30;
			lastTime = currentTime;
		}
	}
}

glm::vec3 getSnakePosition()
{
	return snake_position;
}


void sizeOfSnakeFromInputs(int & snake_size) {
	static double lastTime = glfwGetTime();
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	//add part
	if (glfwGetKey(window, GLFW_KEY_RIGHT_BRACKET) == GLFW_PRESS) {
		if (deltaTime > 0.2f) {
			lastTime = currentTime;
			++snake_size;
			return;
		}
	}
	//remove part
	if (glfwGetKey(window, GLFW_KEY_LEFT_BRACKET) == GLFW_PRESS) {
		if (deltaTime > 0.2f) {
			lastTime = currentTime;
			if (snake_size > 2)
				--snake_size;
			return;
		}
	}
}

void moveMatrixFromInputs()
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
	if (movedeltaTime > 0.01f) {
		snake_position += 0.02f*move_direction*move_snake_speed;
		movelastTime = currentTime;
	}
	// Move backward
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		/*if (movedeltaTime > 0.02) {
		snake_position -= move_direction*0.05f;
		movedeltaTime = currentTime;
		}*/
	}
	// Strafe right
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		if (rotatelastTime > 1.0f / 60.0f) {
			rotate_snake_angle -= dizzy*rotate_snake_speed;
			rotatelastTime = currentTime;
		}
	}
	// Strafe left
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		if (rotatelastTime > 1.0f / 60.0f) {
			rotate_snake_angle += dizzy*rotate_snake_speed;
			rotatelastTime = currentTime;
		}
	}

	MovewMatrix = glm::translate(glm::mat4(1.0), snake_position);
	MovewMatrix = glm::rotate(MovewMatrix, rotate_snake_angle, glm::vec3(0, 1, 0));
}

void setViewMatrix()
{// Reset mouse position for next frame
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),

		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	// Right vector
	glm::vec3 up = glm::vec3(
		0,
		speed,
		0
	);

	float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.


	ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	position = glm::vec3(0, 20, 90);
	verticalAngle = 0;
	horizontalAngle = 3.14f;
	direction = glm::vec3(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);
	ViewMatrix = glm::lookAt(
		position,           // Camera is here
		position + direction, // and looks here : at the same position, plus "direction"
		up              // Head is up (set to 0,-1,0 to look upside-down)
	);
}

void setCameraState(CameraStateEnum c_state)
{
	camera_state = c_state;
}

void computeMatricesFromInputs() {

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
	glfwGetCursorPos(window, &xpos, &ypos);

	// Reset mouse position for next frame
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);


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
		speed,
		0
	);
	// Up vector
	glm::vec3 up = glm::cross(right, direction);

	switch (camera_state)
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
		horizontalAngle = camera_on_snake_angle;
		verticalAngle = -0.2f;
		position = camera_on_snake_position + glm::vec3(0, 2.5, 0);
		break;
	case FREE_VIEW:
		horizontalAngle += mouseSpeed * float(1024 / 2 - xpos);
		verticalAngle += mouseSpeed * float(768 / 2 - ypos);

		// Move forward
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
			position += direction * deltaTime * speed;
		}
		// Move backward
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			position -= direction * deltaTime * speed;
		}
		// Strafe right
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			position += right * deltaTime * speed;
		}
		// Strafe left
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
			position -= right * deltaTime * speed;
		}
		// Strafe up
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			position += up2 * deltaTime * speed;
		}
		// Strafe down
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			position -= up2 * deltaTime * speed;
		}

		break;
	}

	glm::mat4 move_tmp = glm::mat4(1.0);
	// Move forward
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		z -= 0.005;
		move_tmp = glm::translate(glm::mat4(1.0), glm::vec3(z*deltaTime*cos(angle), 0, z*deltaTime*sin(angle)));
	}
	// Move backward
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		z = 0.0;
		angle = 0.0;
		move_tmp = glm::translate(glm::mat4(1.0), glm::vec3(z*cos(angle), 0, z*sin(angle)));
		move_tmp = glm::rotate(move_tmp, angle, glm::vec3(0, 1, 0));
	}
	// Strafe right
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		angle = -deltaTime;
		move_tmp = glm::rotate(move_tmp, angle, glm::vec3(0, 1, 0));
	}
	// Strafe left
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		angle = deltaTime;
		move_tmp = glm::rotate(move_tmp, angle, glm::vec3(0, 1, 0));
	}


	float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.


						   // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	ViewMatrix = glm::lookAt(
		position,           // Camera is here
		position + direction, // and looks here : at the same position, plus "direction"
		up                  // Head is up (set to 0,-1,0 to look upside-down)
	);
	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}

void getMenuMouseState(GameStateEnum & m_state) {
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	//Start Game
	int startx_play = 1024 / 2 * 0.5f;
	int endx_play = 1024 - 0.5f * 1024 / 2;
	int starty_play = (1.0f - 0.4f) * 768 / 2 - 51.0f / 2.0f;
	int endy_play = (1.0f - 0.4f) * 768 / 2 + 51.0f / 2.0f;
	if (xpos > startx_play && xpos < endx_play && ypos > starty_play && ypos < endy_play) {
		m_state = PLAY_GAME;
		menu_state = m_state;
		return;
	}
	//End Game
	startx_play = 1024 / 2 - 100.0f;
	endx_play = 1024 / 2 + 100.0f;
	starty_play = (1.0f + 0.4f) * 768 / 2 - 51.0f / 2.0f;
	endy_play = (1.0f + 0.4f) * 768 / 2 + 51.0f / 2.0f;
	if (xpos > startx_play && xpos < endx_play && ypos > starty_play && ypos < endy_play) {
		m_state = EXIT;
		menu_state = m_state;
		return;
	}
	m_state = MENU;
	menu_state = m_state;
}

void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		if (game_state == MENU)
			game_state = menu_state;
	}
}

void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		switch (game_state) {
		case PLAY_GAME:
			game_state = MENU;
			break;
		case OPTIONS:
			game_state = MENU;
		case MENU:
			game_state = EXIT;
		}
	}
	if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
	{
		camera_state = CLASSIC_VIEW;
	}
	if (key == GLFW_KEY_F2 && action == GLFW_PRESS)
	{
		camera_state = AERIAL_VIEW;
	}
	if (key == GLFW_KEY_F3 && action == GLFW_PRESS)
	{
		camera_state = ON_SNAKE_VIEW;
	}
	if (key == GLFW_KEY_F4 && action == GLFW_PRESS)
	{
		camera_state = FREE_VIEW;
	}
}

GameStateEnum getGameState() {
	return game_state;
}

float getRotateAngle()
{
	return rotate_snake_angle;
}

void setCameraOnSnakePosition(glm::vec3 ConS_position)
{
	camera_on_snake_position = ConS_position;
}

void setCameraOnSnakeAngle(float ConS_angle)
{
	camera_on_snake_angle = ConS_angle;
}

void resetSnakePosition()
{
	// Initial position : on +Z
	position = glm::vec3(0, 0, 5);
	glm::vec3 snake_position = glm::vec3(0, 0, 0);
	// Initial horizontal angle : toward -Z
	horizontalAngle = 3.14f;
	// Initial vertical angle : none
	verticalAngle = 0.0f;
	// Initial Field of View
	initialFoV = 45.0f;

	speed = 10.0f; // 3 units / second
	move_snake_speed = 10.0f; // 3 units / second
	rotate_snake_angle = 0.0;
	rotate_snake_speed = move_snake_speed*0.002f;
	mouseSpeed = 0.005f;
	dizzy = 1;
}
