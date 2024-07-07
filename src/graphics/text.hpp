#pragma once

#include <glm.hpp>
#include <map>
#include "texture.hpp"

struct Character {
	Texture texture;
	glm::ivec2 size;
	glm::ivec2 bearing;
	unsigned int advance;
};

class Text
{
public:
	void loadCharacters();
	std::map<char, Character> characters;
};