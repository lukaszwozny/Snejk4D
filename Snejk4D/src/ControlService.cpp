#include "ControlService.h"

void ControlService::ComputeMatrixFromInput()
{

}

/*
	Getters and setters
*/


glm::mat4 ControlService::getViewMatrix()
{
	return ViewMatrix;
}

glm::mat4 ControlService::getMoveMatrix()
{
	return MovewMatrix;
}
