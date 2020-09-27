#ifndef QUAD_2D_H
#define QUAD_2D_H

#include <GL/glew.h>
#include <glm/glm.hpp>

class Quad2D
{
public:
	Quad2D();
	~Quad2D();

	void init();
	void render();

private:
	GLuint m_vao;

	void setup_mesh();
};

#endif //QUAD_2D_H