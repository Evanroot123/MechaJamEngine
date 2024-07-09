#include "text.hpp"
#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <glad/glad.h>
#include "rectangle.hpp"

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

	for (unsigned char c = 33; c < 128; c++)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "failed to load glyph: " << c << std::endl;
		}

		Texture texture;
		texture.generateText(face);

		Character character = {
			texture, glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top), face->glyph->advance.x
		};
		characters.insert(std::pair<char, Character>(c, character));
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

void Text::loadBatchedCharacters()
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

	Rectangle rectangle{ 512, 512 };
	int currentRowHeight = 0;
	int currentX = 0;
	int currentY = 0;

	for (unsigned char c = 33; c < 128; c++)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "failed to load glyph: " << c << std::endl;
		}

		if (face->glyph->bitmap.rows > currentRowHeight)
			currentRowHeight = face->glyph->bitmap.rows;
		if (currentX + face->glyph->bitmap.width > rectangle.width)
		{
			currentX = 0;
			currentY += currentRowHeight + 1;
			currentRowHeight = 0;
		}

		if (rectangle.canFit(face->glyph->bitmap.width, face->glyph->bitmap.rows, currentX, currentY))
		{
			rectangle.insertData(face->glyph->bitmap.buffer, face->glyph->bitmap.width, face->glyph->bitmap.rows, currentX, currentY);
			CharacterBatched character = { {currentX, currentY}, glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows), 
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top), face->glyph->advance.x };
			batchedCharacters.insert(std::pair<char, CharacterBatched>(c, character));
			currentX += face->glyph->bitmap.width + 1;
		}
		else
		{
			std::cout << "can't fit all glyphs into rectangle" << std::endl;
			return;
		}
	}

	batchedCharactersTexture.generateText2(rectangle);

	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}