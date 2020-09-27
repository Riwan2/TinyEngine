#include "frame_buffer.h"

FrameBuffer::FrameBuffer()
{

}

FrameBuffer::~FrameBuffer()
{
	delete m_texture;

	glDeleteRenderbuffers(GL_RENDERBUFFER, &m_rbo);
	glDeleteFramebuffers(GL_FRAMEBUFFER, &m_fbo);
}

void FrameBuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

void FrameBuffer::init(glm::vec2 size)
{
	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

	init_renderbuffer(size);

	m_texture = new Texture();
	m_texture->init_framebuffer(size);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cerr << "error: frame buffer creation failed." << std::endl;
		throw 1;
	}

	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::init_renderbuffer(glm::vec2 size)
{
	glGenRenderbuffers(1, &m_rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);

	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);
}

void FrameBuffer::resize(glm::vec2 size)
{
	glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);

	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
	m_texture->resize(size);

	glBindRenderbuffer(GL_RENDERBUFFER, 0);	
}