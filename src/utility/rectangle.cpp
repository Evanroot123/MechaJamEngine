#include "rectangle.hpp"

Rectangle::Rectangle(int width, int height) : width(width), height(height)
{
	data = new unsigned char[width * height];
}

Rectangle::~Rectangle()
{
	delete[] data;
}

void Rectangle::insertData(unsigned char* inputData, int inputWidth, int inputHeight, int posX, int posY)
{
	if (!canFit(inputWidth, inputHeight, posX, posY))
		return;


}

bool Rectangle::canFit(int inputWidth, int inputHeight, int posX, int posY)
{

	return true;
}

