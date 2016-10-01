#include "snake.h"


Snake::Snake()
{
	speed = 10.0f;
	size = 0;
	buffer_size = 200.0f / speed;
	for (int i = 0; i < MIN_SIZE; ++i)
		AddPart();
}


Snake::~Snake()
{
}

bool Snake::AddPart()
{
	++size;
	position_buffers_.push_back(new std::queue <glm::vec3>);
	angle_buffers_.push_back(new std::queue <float>);
	return true;
}

bool Snake::RemovePart()
{
	if (size <= MIN_SIZE)
		return false;
	--size;
	delete position_buffers_.back();
	position_buffers_.pop_back();
	delete angle_buffers_.back();
	angle_buffers_.pop_back();
	return true;
}

void Snake::Display(glm::mat4 MVP, glm::vec3 snake_position, float angle)
{
	position_buffers_[0]->push(snake_position);
	if (position_buffers_[0]->size() > buffer_size)
		position_buffers_[0]->pop();
	angle_buffers_[0]->push(angle);
	if (angle_buffers_[0]->size() > buffer_size)
		angle_buffers_[0]->pop();
	glm::mat4 tmp = glm::translate(MVP, snake_position);
	tmp = glm::rotate(tmp, angle, glm::vec3(0, 1, 0));
	snake_head.Display(tmp);
	for (int i = 1; i < size - 6; ++i) {
		//Position queue
		glm::vec3 old_pos = position_buffers_[i - 1]->front();
		position_buffers_[i]->push(old_pos);
		if (position_buffers_[i]->size() > buffer_size)
			position_buffers_[i]->pop();
		//Angle queue
		float old_angle = angle_buffers_[i - 1]->front();
		angle_buffers_[i]->push(old_angle);
		if (angle_buffers_[i]->size() > buffer_size)
			angle_buffers_[i]->pop();
		tmp = glm::translate(MVP, old_pos);
		tmp = glm::rotate(tmp, old_angle, glm::vec3(0, 1, 0));
		snake_part.Display(tmp);
	}
	float scale = 1;
	int tail_buffer = buffer_size;
	float temp = 0;
	for (int i = size - 6; i < size; ++i) {
		//Position queue
		temp += 0.8;
		tail_buffer -= temp;
		glm::vec3 old_pos = position_buffers_[i - 1]->front();
		position_buffers_[i]->push(old_pos);
		if (position_buffers_[i]->size() > tail_buffer)
			position_buffers_[i]->pop();
		//Angle queue
		float old_angle = angle_buffers_[i - 1]->front();
		angle_buffers_[i]->push(old_angle);
		if (angle_buffers_[i]->size() > tail_buffer)
			angle_buffers_[i]->pop();
		tmp = glm::translate(MVP, old_pos);
		tmp = glm::rotate(tmp, old_angle, glm::vec3(0, 1, 0));
		scale -= 0.1;
		tmp = glm::scale(tmp, glm::vec3(scale, scale, scale));
		snake_part.Display(tmp);
	}
}

int Snake::getSize()
{
	return size;
}

std::vector<std::queue<glm::vec3>*> Snake::getPositionBuffers()
{
	return position_buffers_;
}

std::vector<std::queue<float>*> Snake::getAngleBuffers()
{
	return angle_buffers_;
}
