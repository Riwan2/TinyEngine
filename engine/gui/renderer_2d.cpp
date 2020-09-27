#include "renderer_2d.h"

Renderer2D::Renderer2D()
{

}

Renderer2D::~Renderer2D()
{
	delete noise;
	delete m_screenShader;
	delete m_quadShader;
	delete m_quad2D;
}

/*
	render
*/

void Renderer2D::render(Texture* screen)
{
	glDisable(GL_CULL_FACE);

	screen_render(screen);

	m_quadShader->bind();
	m_quadShader->set_mat4("projection", m_projection);

	quad_render();
	texturedQuad_render();

	glEnable(GL_CULL_FACE);
}

/*
	render gui
*/

void Renderer2D::screen_render(Texture* screen)
{	
	m_screenShader->bind();

	static float time = 0;
	time += 0.01f;
	m_screenShader->set_float("time", time);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, screen->textureID());

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, noise->textureID());

	m_screenShader->set_int("aTexture", 0);
	m_screenShader->set_int("aNoise", 1);
	
	m_quad2D->render();
}

void Renderer2D::renderQuad(const glm::vec2&& position, const glm::vec2&& size)
{
	m_quads.push(R_Quad { position, size } );
}

void Renderer2D::renderTexturedQuad(const glm::vec2&& position, const glm::vec2&& size, Texture* texture)
{
	m_texturedQuads.push(R_TexturedQuad { position, size, texture } );
}

/*
	render specific methode
*/

void Renderer2D::quad_render()
{
	while (!m_quads.empty()) {
		R_Quad quad = m_quads.front();
	
		m_quadShader->set_mat4("model", quad_model(quad.position, quad.size));
		m_quad2D->render();

		m_quads.pop();
	}
}

void Renderer2D::texturedQuad_render()
{
	while (!m_texturedQuads.empty()) {
		R_TexturedQuad quad = m_texturedQuads.front();

		quad.texture->bind();

		m_quadShader->set_mat4("model", quad_model(quad.position, quad.size));
		m_quadShader->set_bool("textured", true);
		m_quad2D->render();

		m_texturedQuads.pop();
	}
}

/*
	quad util
*/

glm::mat4 Renderer2D::quad_model(glm::vec2 position, glm::vec2 size)
{
	glm::mat4 model = glm::mat4(1.0);
	glm::vec2 mySize = size / 2.0f;
	model = glm::translate(model, glm::vec3(position.x + mySize.x, position.y + mySize.y, 0.0f));
	model = glm::scale(model, glm::vec3(mySize.x, mySize.y, 0.0f));
	return model;
}

/*
	init
*/

void Renderer2D::init(glm::vec2 displaySize)
{
	m_quad2D = new Quad2D();
	m_quad2D->init();
			
	m_quadShader = new Shader();
	m_quadShader->load("gui/basic.vr", "gui/basic.fa");

	m_screenShader = new Shader();
	m_screenShader->load("screen.vr", "screen.fa");

	noise = new Texture();
	noise->load("noise.jpg");

	resize(displaySize);
}

void Renderer2D::resize(glm::vec2 displaySize)
{
	m_projection = glm::mat4(1.0);
	m_projection = glm::ortho(0.0f, displaySize.x, displaySize.y, 0.0f, -1.0f, 1.0f);
}