#pragma once
#include "gl_includes.h"
#include <vector>

class Food
{
public:
	Food(char* obj_path, char* tex_path);
	~Food();
	void Display(glm::mat4 MVP);
	glm::mat4 getMVP();
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
