#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <vector>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "../basic/base.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	void load(const std::string&& filename, bool info = false);
	void init(Vertex* vertices, int numVertices, GLuint* indices, int numIndices);
	void render();

private:
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;

	Vertex* m_vertices;
	GLuint* m_indices;
	int m_numVertices;
	int m_numIndices;

	void setup_mesh(Vertex* vertices, int numVertices, GLuint* indices, int numIndices);
	void load_from_file(const char* filename, bool info);
};

#endif //MESH_H