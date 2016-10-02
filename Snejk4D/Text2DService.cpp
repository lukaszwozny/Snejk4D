#include "Text2DService.h"
#include "FileService.h"


Text2DService::Text2DService()
{
}


Text2DService::~Text2DService()
{
}

void Text2DService::initText2D(const char* texturePath)
{

	// Initialize texture
	Text2DTextureID = FileService::loadDDS(texturePath);

	// Initialize VBO
	glGenBuffers(1, &Text2DVertexBufferID);
	glGenBuffers(1, &Text2DUVBufferID);

	// Initialize Shader
	Text2DShaderID = FileService::LoadShaders("TextVertexShader.vertexshader", "TextVertexShader.fragmentshader");

	// Initialize uniforms' IDs
	Text2DUniformID = glGetUniformLocation(Text2DShaderID, "myTextureSampler");

}

void Text2DService::printText2D(const char* text, int x, int y, int size)
{
}

void Text2DService::cleanupText2D()
{
}
