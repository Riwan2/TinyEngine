#include "renderer_2d.h"

/*
	variable
*/

Quad2D *Renderer2D::m_quad2D;
Shader *Renderer2D::m_quadShader;

glm::mat4 Renderer2D::m_projection;

std::queue<R_Quad> Renderer2D::m_quads;
std::queue<R_TexturedQuad> Renderer2D::m_textureQuads;
std::queue<R_ShaderQuad> Renderer2D::m_shaderQuads;

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
	render
*/

void Renderer2D::render()
{
	glDisable(GL_CULL_FACE);

	shaderQuad_render();

	m_quadShader->bind();
	m_quadShader->set_mat4("projection", m_projection);

	quad_render();
	textureQuad_render();

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
	add to render list
*/

void Renderer2D::renderQuad(const glm::vec2&& position, const glm::vec2&& size, const glm::vec3&& color)
{
	m_quads.push(R_Quad { position, size, glm::vec4(color, 1.0) } );
}

void Renderer2D::renderQuad(const glm::vec2 &&position, const glm::vec2 &&size, const glm::vec4 &&color)
{
	m_quads.push(R_Quad{position, size, color});
}

void Renderer2D::renderTextureQuad(const glm::vec2&& position, const glm::vec2&& size, Texture* texture)
{
	m_textureQuads.push(R_TexturedQuad { position, size, texture } );
}

void Renderer2D::renderShaderQuad(const glm::vec2&& position, const glm::vec2&& size, Shader* shader)
{
	m_shaderQuads.push(R_ShaderQuad { position, size, shader } );
}

/*
	render specific methode
*/

//basic quad
void Renderer2D::quad_render()
{
	while (!m_quads.empty()) {
		R_Quad quad = m_quads.front();
	
		m_quadShader->set_mat4("model", quad_model(quad.position, quad.size));
		m_quadShader->set_vec4("color", quad.color);
		m_quad2D->render();

		m_quads.pop();
	}
}

//texture quad
void Renderer2D::textureQuad_render()
{
	while (!m_textureQuads.empty()) {
		R_TexturedQuad quad = m_textureQuads.front();

		quad.texture->bind();

		m_quadShader->set_mat4("model", quad_model(quad.position, quad.size));
		m_quadShader->set_bool("textured", true);
		m_quad2D->render();

		m_textureQuads.pop();
	}
}

//shader quad
void Renderer2D::shaderQuad_render()
{
	while (!m_shaderQuads.empty()) {
		R_ShaderQuad quad = m_shaderQuads.front();

		Shader* shader = quad.shader;
		shader->set_mat4("model", quad_model(quad.position, quad.size));
		shader->set_mat4("projection", m_projection);
		m_quad2D->render();

		m_shaderQuads.pop();
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

void Renderer2D::resize(glm::vec2 displaySize)
{
	m_projection = glm::mat4(1.0);
	m_projection = glm::ortho(0.0f, displaySize.x, displaySize.y, 0.0f, -1.0f, 1.0f);
}