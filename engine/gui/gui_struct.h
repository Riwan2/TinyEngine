#ifndef GUI_STRUCT_H
#define GUI_STRUCT_H

#include <glm/glm.hpp>

#include "../ressource/texture.h"

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

#endif //GUI_STRUCT_H