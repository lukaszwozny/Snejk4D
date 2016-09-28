#pragma once
#include <vector>
#include <queue>
#include "snake_part.h"
#include "snake_head.h"
#include "snake_tail.h"

class Snake
{
public:
	Snake();
	~Snake();
	bool AddPart();
	bool RemovePart();
	void Display(glm::mat4 MVP, glm::vec3 snake_position, float angle);
	int getSize();
	std::vector < std::queue <glm::vec3>* > getPositionBuffers();
	std::vector < std::queue <float>* > getAngleBuffers();
private:
	const int MIN_SIZE = 7;
	int size;
	int buffer_size;
	SnakeHead snake_head;
	SnakePart snake_part;
	SnakeTail snake_tail;
	std::vector < std::queue <glm::vec3>* > position_buffers_;
	std::vector < std::queue <float>* > angle_buffers_;
};

