#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include "../ressource/texture.h"

class FrameBuffer
{
public:
	FrameBuffer();
	~FrameBuffer();

	void init(glm::vec2 size);
	void bind();

	void resize(glm::vec2 size);

	GLuint textureID() { return m_texture->textureID(); }
	Texture* texture() { return m_texture; }

private:
	GLuint m_fbo;
	GLuint m_rbo;
	Texture* m_texture;

	void init_renderbuffer(glm::vec2 size);
};

#endif //FRAME_BUFFER_H