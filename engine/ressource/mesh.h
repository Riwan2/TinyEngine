#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <vector>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};

class Mesh
{
public:
	Mesh();
	~Mesh();

	void load(const std::string&& filename, bool info = false);
	void init(Vertex* vertices, int numVertices, GLuint* indices, int numIndices);
	void render();

	int numVertices() { return m_numVertices;}

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