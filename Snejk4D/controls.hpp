#ifndef CONTROLS_HPP
#define CONTROLS_HPP
#include "gl_includes.h"

void moveMatrixFromInputs(GLFWwindow* window);
void computeMatricesFromInputs(GLFWwindow* window);
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();
glm::mat4 getMoveMatrix();

glm::vec3 getSnakePosition();
float getSnakeSpeed();
float getRotateAngle();

#endif