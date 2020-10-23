#ifndef RENDERER_2D_H
#define RENDERER_2D_H

#include "../mesh/quad_2d.h"
#include "gui_struct.h"

#include <queue>

class Renderer2D
{
public:
	static void init(glm::vec2 displaySize);
	static void resize(glm::vec2 displaySize);

	static void begin(bool customShader = false);
	static void end();

	static void cleanup();

	//screen
	static void render_screen();

	//render quad to 2d screen
	static void renderQuad(const glm::vec2 &&position, const glm::vec2 &&size, const glm::vec3 &&color = glm::vec3(1.0, 1.0, 1.0));
	static void renderQuad(const glm::vec2 &&position, const glm::vec2 &&size, const glm::vec4 &&color);

	static void renderTextureQuad(const glm::vec2&& position, const glm::vec2&& size, Texture* texture);
	static void renderShaderQuad(const glm::vec2 &&position, const glm::vec2 &&size, Shader *shader);

private:
	static Quad2D* m_quad2D;
	static Shader *m_quadShader;

	static glm::mat4 m_projection;
	
	//util
	static glm::mat4 quad_model(glm::vec2 position, glm::vec2 size);

};

#endif //RENDERER_2D_H