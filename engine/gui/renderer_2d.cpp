#include "renderer_2d.h"

/*
	variable
*/

Quad2D *Renderer2D::m_quad2D;
Shader *Renderer2D::m_quadShader;

glm::mat4 Renderer2D::m_projection;

/*
	clean up
*/

void Renderer2D::cleanup()
{
	delete m_quadShader;
	delete m_quad2D;
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

	resize(displaySize);
}

/*
	begin
*/

void Renderer2D::begin(bool customShader)
{
	glDisable(GL_CULL_FACE);

	if (!customShader) {
		m_quadShader->bind();
		m_quadShader->set_mat4("projection", m_projection);
	}
}

/*
	end
*/

void Renderer2D::end()
{
	glEnable(GL_CULL_FACE);
}

/*
	render screen effect
*/

void Renderer2D::render_screen()
{	
	m_quad2D->render();
}

/*
	render
*/

void Renderer2D::renderQuad(const glm::vec2&& position, const glm::vec2&& size, const glm::vec3&& color)
{
	m_quadShader->set_mat4("model", quad_model(position, size));
	m_quadShader->set_vec4("color", glm::vec4(color, 1.0));
	m_quad2D->render();
}

void Renderer2D::renderQuad(const glm::vec2 &&position, const glm::vec2 &&size, const glm::vec4 &&color)
{
	m_quadShader->set_mat4("model", quad_model(position, size));
	m_quadShader->set_vec4("color", color);
	m_quad2D->render();
}

void Renderer2D::renderTextureQuad(const glm::vec2&& position, const glm::vec2&& size, Texture* texture)
{
	texture->bind();
	m_quadShader->set_mat4("model", quad_model(position, size));
	m_quadShader->set_bool("textured", true);
	m_quad2D->render();
}

void Renderer2D::renderShaderQuad(const glm::vec2&& position, const glm::vec2&& size, Shader* shader)
{
	shader->set_mat4("model", quad_model(position, size));
	shader->set_mat4("projection", m_projection);
	m_quad2D->render();
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

void Renderer2D::resize(glm::vec2 displaySize)
{
	m_projection = glm::mat4(1.0);
	m_projection = glm::ortho(0.0f, displaySize.x, displaySize.y, 0.0f, -1.0f, 1.0f);
}