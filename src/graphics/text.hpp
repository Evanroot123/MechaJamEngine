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

struct CharacterBatched {
	glm::ivec2 pos;
	glm::ivec2 size;
	glm::ivec2 bearing;
	unsigned int advance;
};

class Text
{
public:
	Text(int pixelHeight = 48);
	void loadCharacters();
	void loadBatchedCharacters();

	int pixelHeight = 48;
	std::map<char, Character> characters;
	std::map<char, CharacterBatched> batchedCharacters;
	Texture batchedCharactersTexture;
};