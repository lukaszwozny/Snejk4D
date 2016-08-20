#pragma once
#include "gl_includes.h"
#include <vector>

class FileService
{
public:
	static GLuint LoadBMP(const char * imagepath);
	static GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
	static bool LoadOBJ(const char * path, std::vector<glm::vec3> & out_vertices, std::vector<glm::vec2> & out_uvs, std::vector<glm::vec3> & out_normals);
};
