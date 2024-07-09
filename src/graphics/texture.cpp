#pragma once

#include <iostream>
#include <vector>
#include "texture.hpp"

Texture::Texture()
	: width(0), height(0), internalFormat(GL_RGB), imageFormat(GL_RGB), wrapS(GL_REPEAT), wrapT(GL_REPEAT), filterMin(GL_LINEAR), filterMax(GL_LINEAR)
{
	glGenTextures(1, &id);
}

void Texture::generate(unsigned int width, unsigned int height, unsigned char* data)
{
	if (currentUnpackAlignment != 4)
	{
		currentUnpackAlignment = 4;
		glPixelStorei(GL_UNPACK_ALIGNMENT, currentUnpackAlignment);
	}

	this->width = width;
	this->height = height;

	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMax);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);
}

void Texture::generateText(FT_Face& face)
{
	if (currentUnpackAlignment != 1)
	{
		currentUnpackAlignment = 1;
		glPixelStorei(GL_UNPACK_ALIGNMENT, currentUnpackAlignment);
	}

	this->width = face->glyph->bitmap.width * 2;
	this->height = face->glyph->bitmap.rows;

	std::vector<unsigned char> data1;
	int size = face->glyph->bitmap.width * face->glyph->bitmap.rows;
	data1.resize(size * 2);

	int tempWidth = face->glyph->bitmap.width;
	int curWidth = 0;
	int row = 0;
	for (int i = 0; i < size; i++)
	{
		//data1.push_back(face->glyph->bitmap.buffer[i]);
		//data1.push_back(face->glyph->bitmap.buffer[i]);
		data1[curWidth + row * tempWidth * 2] = face->glyph->bitmap.buffer[i];
		data1[curWidth + tempWidth + row * tempWidth * 2] = face->glyph->bitmap.buffer[i];

		curWidth++;
		if (curWidth >= tempWidth)
		{
			row++;
			curWidth = 0;
		}
	}
	for (int i = 0; i < size; i++)
	{
		//data1.push_back(face->glyph->bitmap.buffer[i]);
	}
	
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width * 2, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, data1.data());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::generateText2(Rectangle& rectangle)
{
	if (currentUnpackAlignment != 1)
	{
		currentUnpackAlignment = 1;
		glPixelStorei(GL_UNPACK_ALIGNMENT, currentUnpackAlignment);
	}

	width = rectangle.width;
	height = rectangle.height;

	//Rectangle rectangle{ (int)width, (int)height };
	//rectangle.insertData(face->glyph->bitmap.buffer, face->glyph->bitmap.width, height, 0, 0);
	//rectangle.insertData(face->glyph->bitmap.buffer, face->glyph->bitmap.width, height, face->glyph->bitmap.width, 0);

	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, rectangle.data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, id);
}