#include "text.hpp"
#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <glad/glad.h>

void Text::loadCharacters()
{
	const char* fontFile = "resources/fonts/arial.ttf";
	//fs::exists(fontFile) ? std::cout << "file exists" : std::cout << "file doesn't exist";

	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		return;
	}

	FT_Face face;
	if (FT_New_Face(ft, fontFile, 0, &face))
	{
		return;
	}

	FT_Set_Pixel_Sizes(face, 0, 48);
	if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
	{
		return;
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for (unsigned char c = 33; c < 128; c++)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "failed to load glyph: " << c << std::endl;
		}

		//std::cout << c << ": " << face->glyph->bitmap.width << ", " << face->glyph->bitmap.rows << "\n";

		Texture texture;
		//texture.generateText(face);
		texture.generateText2(face);

		Character character = {
			texture, glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top), face->glyph->advance.x
		};
		characters.insert(std::pair<char, Character>(c, character));
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}