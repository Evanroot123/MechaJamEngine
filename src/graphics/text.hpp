#pragma once

#include <glm.hpp>

struct Character {
	unsigned int textureID;
	glm::ivec2 size;
	glm::ivec2 bearing;
	unsigned int advance;
};

class Text
{
	void loadCharacters();
};