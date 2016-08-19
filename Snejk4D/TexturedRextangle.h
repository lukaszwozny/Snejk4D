#pragma once
#include "gl_includes.h"
#include <vector>

class TexturedRextangle
{
public:
	void Initialize(char* texture_path);
	void Display(glm::vec3 pos);
	~TexturedRextangle();

protected:
	TexturedRextangle();
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

private:
	float width;
	float height;

public:
	float getWidth() const;
	void setWidth(float width);
	float getHeight() const;
	void setHeight(float height);
};
