#pragma once
#include "gl_includes.h"

class FileService
{
public:
	static GLuint LoadBMP(const char * imagepath);
	static GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
};
