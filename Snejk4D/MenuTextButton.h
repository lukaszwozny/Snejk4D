#pragma once
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLM
#include <glm/gtc/matrix_transform.hpp>

class MenuTextButton
{
public:
	MenuTextButton(char* path);
	void Display(glm::vec3 pos);
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
