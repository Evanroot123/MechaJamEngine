#pragma once

#include <iostream>
#include "texture.hpp"



Texture2D::Texture2D()
	: width(0), height(0), internalFormat(GL_RGB), imageFormat(GL_RGB), wrapS(GL_REPEAT), wrapT(GL_REPEAT), filterMin(GL_LINEAR), filterMax(GL_LINEAR)
{
	glGenTextures(1, &id);
}

void Texture2D::generate(unsigned int width, unsigned int height, unsigned char* data)
{
	if (currentUnpackAlignment != 4)
	{
		currentUnpackAlignment = 4;
		glPixelStorei(GL_UNPACK_ALIGNMENT, currentUnpackAlignment);
	}

	this->width = width;
	this->height = height;

	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMax);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::generateText(FT_Face& face)
{
	if (currentUnpackAlignment != 1)
	{
		currentUnpackAlignment = 1;
		glPixelStorei(GL_UNPACK_ALIGNMENT, currentUnpackAlignment);
	}

	this->width = face->glyph->bitmap.width;
	this->height = face->glyph->bitmap.rows;
	
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture2D::bind() const
{
	glBindTexture(GL_TEXTURE_2D, id);
}