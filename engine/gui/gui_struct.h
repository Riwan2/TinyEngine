#ifndef GUI_STRUCT_H
#define GUI_STRUCT_H

#include <glm/glm.hpp>

#include "../ressource/texture.h"
#include "../ressource/shader.h"

struct R_Quad
{
	glm::vec2 position;
	glm::vec2 size;
};

struct R_TexturedQuad
{
	glm::vec2 position;
	glm::vec2 size;
	Texture* texture;
};

struct R_ShaderQuad
{
	glm::vec2 position;
	glm::vec2 size;
	Shader* shader;
};

#endif //GUI_STRUCT_H