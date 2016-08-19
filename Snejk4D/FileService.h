#pragma once
// Include GLEW
#include <GL/glew.h>

class FileService
{
public:
	static GLuint LoadBMP(const char * imagepath);
	static GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
};
