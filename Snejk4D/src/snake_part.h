#pragma once
#include "gl_includes.h"
#include <vector>

class SnakePart
{
public:
	SnakePart();
	~SnakePart();
	void Display(glm::mat4 MVP);
private:
	GLuint programID;
	GLuint Texture;
	GLuint TextureID;
	GLuint MatrixID;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals; // Won't be used at the moment.

	GLuint vertexbuffer;
	GLuint uvbuffer;
	glm::mat4 ModelMatrix;
	glm::mat4 MVP;
};
