#pragma once
#include "gl_includes.h"
class TimeElement
{
public:
	TimeElement();
	~TimeElement();

	void updatePrevTime();
	void updateActualTime();


	double getElapsedTime() const;
private:
	double prev_time_;
	double actual_time_;
};

