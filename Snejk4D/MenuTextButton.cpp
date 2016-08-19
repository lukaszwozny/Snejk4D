#include "MenuTextButton.h"
#include "FileService.h"

MenuTextButton::MenuTextButton(char* path)
{
//	// Create and compile our GLSL program from the shaders
//	programID = LoadShaders("shaders/MenuTextVertexShader.vertexshader", "shaders/MenuTextFragmentShader.fragmentshader");
//
	Texture = FileService::LoadBMP(path);
//	// Get a handle for our "myTextureSampler" uniform
//	TextureID = glGetUniformLocation(programID, "myTextureSampler");
//
//	// Get a handle for our "MVP" uniform
//	MatrixID = glGetUniformLocation(programID, "MVP");
//	float width = 330.0f / 660.0f;
//	float height = 51.0f / 660.0f;
//	const GLfloat scene_points[] = {
//		-width, -height, 0.0f,
//		width, -height, 0.0f,
//		width, height, 0.0f,
//
//		width, height, 0.0f,
//		-width, height, 0.0f,
//		-width, -height, 0.0f,
//	};
//
//	GLfloat tex_coords[] = {
//		0.0f, 0.0f, // A
//		1.0f, 0.0f, // B
//		1.0f, 1.0f, // C
//		1.0f, 1.0f, // D
//		0.0f, 1.0f, // E
//		0.0f, 0.0f, // F
//	};
//	glGenBuffers(1, &vertexbuffer);
//	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(scene_points), &scene_points[0], GL_STATIC_DRAW);
//
//	glGenBuffers(1, &uvbuffer);
//	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(tex_coords), tex_coords, GL_STATIC_DRAW);
}
