#pragma once

#include <glad/glad.h>

#include <ft2build.h>
#include FT_FREETYPE_H

class Texture
{
public:
	unsigned int id;
	unsigned int width, height;
	unsigned int internalFormat;
	unsigned int imageFormat;
	unsigned int wrapS;
	unsigned int wrapT;
	unsigned int filterMin;
	unsigned int filterMax;

	unsigned int currentUnpackAlignment = 4;

	Texture();
	void generate(unsigned int width, unsigned int height, unsigned char* data);
	void generateText(FT_Face& face);
	void generateText2(FT_Face& face);
	void bind() const;
};