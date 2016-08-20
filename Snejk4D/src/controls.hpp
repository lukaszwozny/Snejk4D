#ifndef CONTROLS_HPP
#define CONTROLS_HPP
#include "gl_includes.h"

void computeMatricesFromInputs(GLFWwindow* window);
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();

#endif