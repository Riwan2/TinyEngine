#include "quad_2d.h"

const int NUM_VERTICES = 4;
const int NUM_INDICES = 6;

Quad2D::Quad2D()
{

}

Quad2D::~Quad2D()
{
	glDeleteVertexArrays(1, &m_vao);
}

void Quad2D::render()
{
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, NUM_INDICES, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Quad2D::init()
{
	setup_mesh();
}

void Quad2D::setup_mesh()
{
	GLuint vbo, ebo;

	glm::vec2 vertices[NUM_VERTICES] {
		glm::vec2(-1.0,  1.0),
		glm::vec2(-1.0, -1.0),
		glm::vec2( 1.0, -1.0),
		glm::vec2( 1.0,  1.0),
	};

	GLuint indices[NUM_INDICES] {
		0, 1, 2,
		2, 3, 0,
	};

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, NUM_VERTICES * sizeof(glm::vec2), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, NUM_INDICES * sizeof(GLuint), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	glBindVertexArray(0);

	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}