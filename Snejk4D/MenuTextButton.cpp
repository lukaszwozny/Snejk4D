#include "MenuTextButton.h"
#include "FileService.h"

MenuTextButton::MenuTextButton(char* path)
{
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	float width = 330.0f / 660.0f;
	float height = 51.0f / 660.0f;
	// An array of 3 vectors which represents 3 vertices
	static const GLfloat g_vertex_buffer_data[] = {
		-width, -height, 0.0f,
		width, -height, 0.0f,
		width, height, 0.0f,

		width, height, 0.0f,
		-width, height, 0.0f,
		-width, -height, 0.0f,
	};

	GLfloat tex_coords[] = {
		0.0f, 0.0f, // A
		1.0f, 0.0f, // B
		1.0f, 1.0f, // C
		1.0f, 1.0f, // D
		0.0f, 1.0f, // E
		0.0f, 0.0f, // F
	};

	// This will identify our vertex buffer
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

void MenuTextButton::Display(glm::vec3 pos)
{
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 6); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);

}
