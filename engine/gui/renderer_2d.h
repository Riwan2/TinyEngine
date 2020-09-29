#ifndef RENDERER_2D_H
#define RENDERER_2D_H

#include "../mesh/quad_2d.h"
#include "gui_struct.h"

#include <queue>

class Renderer2D
{
public:
	Renderer2D();
	~Renderer2D();

	void init(glm::vec2 displaySize);
	void resize(glm::vec2 displaySize);

	void render();

	//screen
	void render_screen();

	void renderQuad(const glm::vec2&& position, const glm::vec2&& size);
	void renderTextureQuad(const glm::vec2&& position, const glm::vec2&& size, Texture* texture);
	void renderShaderQuad(const glm::vec2&& position, const glm::vec2&& size, Shader* shader);

private:
	Quad2D* m_quad2D;
	Shader* m_quadShader;

	glm::mat4 m_projection;

	std::queue<R_Quad> m_quads;
	std::queue<R_TexturedQuad> m_textureQuads;
	std::queue<R_ShaderQuad> m_shaderQuads;

	//render
	void quad_render();
	void textureQuad_render();
	void shaderQuad_render();

	//util
	glm::mat4 quad_model(glm::vec2 position, glm::vec2 size);

};

#endif //RENDERER_2D_H