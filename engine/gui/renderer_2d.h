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

	void render(Texture* screen);

	void renderQuad(const glm::vec2&& position, const glm::vec2&& size);
	void renderTexturedQuad(const glm::vec2&& position, const glm::vec2&& size, Texture* texture);
	void renderCustomShaderQuad(const glm::vec2&& position, const glm::vec2&& size, Shader* shader);

private:
	Quad2D* m_quad2D;
	
	Shader* m_quadShader;
	Shader* m_screenShader;

	glm::mat4 m_projection;

	Texture* noise;

	std::queue<R_Quad, std::deque<R_Quad>> m_quads;
	std::queue<R_TexturedQuad, std::deque<R_TexturedQuad>> m_textureQuads;
	std::queue<R_ShaderQuad, std::deque<R_ShaderQuad>> m_shaderQuads;

	//screen
	void screen_render(Texture* screen);

	//render
	void quad_render();
	void texturedQuad_render();

	//util
	glm::mat4 quad_model(glm::vec2 position, glm::vec2 size);

};

#endif //RENDERER_2D_H