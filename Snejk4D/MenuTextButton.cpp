#include "MenuTextButton.h"
#include "FileService.h"
#include "game.h"

MenuTextButton::MenuTextButton(float width, float height, char* texture_path)
{
	setWidth(width);
	setHeight(height);
	Initialize(texture_path);
}

MenuTextButton::~MenuTextButton()
{
	// Cleanup VBO and shader
	glDeleteProgram(programID);
	glDeleteTextures(1, &TextureID);
}

