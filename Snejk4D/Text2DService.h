#pragma once
#include "gl_includes.h"
class Text2DService
{
public:
	Text2DService();
	~Text2DService();
	void initText2D(const char * texturePath);
	void printText2D(const char * text, int x, int y, int size);
	void cleanupText2D();
private:
	unsigned int Text2DTextureID;
	unsigned int Text2DVertexBufferID;
	unsigned int Text2DUVBufferID;
	unsigned int Text2DShaderID;
	unsigned int Text2DUniformID;
};

