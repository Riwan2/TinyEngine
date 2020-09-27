#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture()
{

}

Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}

/*
	bind
*/

void Texture::bind(GLenum sampler)
{
	glActiveTexture(sampler);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

/*
	init 2d texture from file
*/

void Texture::load(const std::string&& filename)
{
	std::string extension;
	if (filename.find(".") != std::string::npos) {
		extension = filename.substr(filename.find("."));
	} else {
		throw std::runtime_error("error: no file extension [" + filename + "].");
	}

	if (extension == ".jpg")
		init(("../ressource/texture/" + filename).c_str(), GL_RGB);
	else if (extension == ".png")
		init(("../ressource/texture/" + filename).c_str(), GL_RGBA);
	else {
		std::cerr << "error: invalid file extension[" << filename << "]." << '\n';
	}
}

void Texture::init(const char* filename, GLint internalFormat)
{
	int nrChannels;
 	m_data = stbi_load(filename, &m_width, &m_height, &m_nrChannels, 0);
 	
 	if (!m_data) {
 		throw std::runtime_error(std::string("error: can't open texture file [") + filename + "].");
 	}

 	setup_texture(internalFormat);
 	stbi_image_free(m_data);
}

void Texture::setup_texture(GLint internalFormat)
{
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, internalFormat, GL_UNSIGNED_BYTE, m_data);

    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

/*
	init texture for frame buffer
*/

void Texture::init_framebuffer(glm::vec2 size)
{
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::resize(glm::vec2 size)
{
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);
}