#pragma once

#include <glad/glad.h>

class FT_Face;

class Texture2D
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

	Texture2D();
	void generate(unsigned int width, unsigned int height, unsigned char* data);
	void generateText(FT_Face& face);
	void bind() const;
};