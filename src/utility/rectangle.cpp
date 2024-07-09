#include "rectangle.hpp"
#include <cstring>

Rectangle::Rectangle(int width, int height) : width(width), height(height)
{
	data = new unsigned char[width * height];
	memset(data, 0, width * height);
}

Rectangle::~Rectangle()
{
	delete[] data;
}

void Rectangle::insertData(unsigned char* inputData, int inputWidth, int inputHeight, int posX, int posY)
{
	if (!canFit(inputWidth, inputHeight, posX, posY))
		return;

	for (int i = 0; i < inputWidth; i++)
	{
		for (int j = 0; j < inputHeight; j++)
		{
			data[(j + posY) * width + (i + posX)] = inputData[j * inputWidth + i];
		}
	}
}

bool Rectangle::canFit(int inputWidth, int inputHeight, int posX, int posY)
{
	if ((width - posX >= inputWidth) && (height - posY >= inputHeight))
		return true;
	else
		return false;
}

