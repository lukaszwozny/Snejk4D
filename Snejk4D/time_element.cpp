#include "time_element.h"


TimeElement::TimeElement()
{
}


TimeElement::~TimeElement()
{
}

void TimeElement::updatePrevTime()
{
	prev_time_ = glfwGetTime();
}

void TimeElement::updateActualTime()
{
	actual_time_ = glfwGetTime();
}

double TimeElement::getElapsedTime() const
{
	return actual_time_ - prev_time_;
}
