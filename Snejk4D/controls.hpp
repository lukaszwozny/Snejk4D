#ifndef CONTROLS_HPP
#define CONTROLS_HPP

#include "gl_includes.h"

void getMenuMouseState(GameStateEnum & m_state);
void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
GameStateEnum getGameState();
float getRotateAngle();
void setCameraOnSnakePosition(glm::vec3 ConS_position);
void setCameraOnSnakeAngle(float ConS_angle);
void resetSnakePosition();

void setViewMatrix();
void setCameraState(CameraStateEnum c_state);
void sizeOfSnakeFromInputs(int & snake_size);
void moveMatrixFromInputs();
void computeMatricesFromInputs();
void getRandomFood(int &rand_x, int &rand_z);
glm::vec3 getSnakePosition();
glm::mat4 getViewMatrix();
glm::mat4 getMoveMatrix();
int getSizeOfSnake();
int getDizzyState();
void setDizzyState(int state);
float getSnakeSpeed();
glm::mat4 getProjectionMatrix();
#endif
