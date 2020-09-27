#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <iostream>
#include <string>

#include <glm/glm.hpp>

class Texture
{
public:
	Texture();
	~Texture();

	void load(const std::string&& filename);
	
	void init_framebuffer(glm::vec2 size);

	void bind(GLenum sampler = GL_TEXTURE0);
	void resize(glm::vec2 size);

	int width() { return m_width; }
	int height() { return m_height; }
	int nrChannels() { return m_nrChannels;}

	GLuint textureID() { return m_texture; }

private:
	GLuint m_texture;
	unsigned char* m_data;
	
	int m_width;
	int m_height;
	int m_nrChannels;

	void init(const char* filename, GLint internalFormat);
	void setup_texture(GLint internalFormat);
};

#endif //TEXTURE_H