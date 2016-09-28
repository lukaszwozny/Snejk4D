#include "food.h"
#include "FileService.h"

Food::Food(char * obj_path, char * tex_path)
{
	// Create and compile our GLSL program from the shaders
	programID = FileService::LoadShaders("shaders/TransformVertexShader.vertexshader", "shaders/TextureFragmentShader.fragmentshader");

	//GLuint Texture = loadDDS("textures/uvmap.DDS");
	Texture = FileService::LoadBMP(tex_path);

	// Get a handle for our "myTextureSampler" uniform
	TextureID = glGetUniformLocation(programID, "myTextureSampler");

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(programID, "MVP");

	// Read our .obj file
	bool res = FileService::LoadOBJ(obj_path, vertices, uvs, normals);

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
}

Food::~Food()
{
}
