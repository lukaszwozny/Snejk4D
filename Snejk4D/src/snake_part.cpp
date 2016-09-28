#include "snake_part.h"
#include "FileService.h"

SnakePart::SnakePart()
{
	// Create and compile our GLSL program from the shaders
	programID = FileService::LoadShaders("shaders/TransformVertexShader.vertexshader", "shaders/TextureFragmentShader.fragmentshader");

	Texture = FileService::LoadBMP("textures/creeper_body.bmp");
	// Get a handle for our "myTextureSampler" uniform
	TextureID = glGetUniformLocation(programID, "myTextureSampler");

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(programID, "MVP");

	// Read our .obj file
	bool res = FileService::LoadOBJ("models/cube.obj", vertices, uvs, normals);

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
}

SnakePart::~SnakePart()
{
	// Cleanup VBO and shader
	glDeleteProgram(programID);
	glDeleteTextures(1, &TextureID);
}

void SnakePart::Display(glm::mat4 MVP)
{
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	//// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	//// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(TextureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
