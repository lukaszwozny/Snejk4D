#include "controls.hpp"

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;
glm::mat4 MovewMatrix;

glm::mat4 getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix(){
	return ProjectionMatrix;
}
glm::mat4 getMoveMatrix() {
	return MovewMatrix;
}

// Initial position : on +Z
glm::vec3 position = glm::vec3( 0, 0, 5 ); 
// initial snake positon
glm::vec3 snake_position = glm::vec3(0, 0, 0);
// Initial horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 3.0f; // 3 units / second
float move_snake_speed = 10.0f; // 3 units / second
float rotate_snake_angle = 0.0;
float rotate_snake_speed = move_snake_speed*0.002f;
float mouseSpeed = 0.005f;
int dizzy = 1;


glm::vec3 getSnakePosition()
{
	return snake_position;
}

float getSnakeSpeed()
{
	return move_snake_speed;
}

float getRotateAngle()
{
	return rotate_snake_angle;
}

void moveMatrixFromInputs(GLFWwindow* window)
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


void computeMatricesFromInputs(GLFWwindow* window){

	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	// Reset mouse position for next frame
	glfwSetCursorPos(window, 1024/2, 768/2);

	// Compute new orientation
	horizontalAngle += mouseSpeed * float(1024/2 - xpos );
	verticalAngle   += mouseSpeed * float( 768/2 - ypos );

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);
	
	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f), 
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);
	
	// Up vector
	glm::vec3 up = glm::cross( right, direction );

	// Move forward
	if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
		position += direction * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
		position -= direction * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
		position += right * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
		position -= right * deltaTime * speed;
	}

	float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	ViewMatrix       = glm::lookAt(
								position,           // Camera is here
								position+direction, // and looks here : at the same position, plus "direction"
								up                  // Head is up (set to 0,-1,0 to look upside-down)
						   );

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}