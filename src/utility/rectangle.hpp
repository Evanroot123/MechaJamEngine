#pragma once


class Rectangle
{
public:
	Rectangle(int width, int height);
	~Rectangle();
	void insertData(unsigned char* inputData, int inputWidth, int inputHeight, int posX, int posY);
	bool canFit(int inputWidth, int inputHeight, int posX, int posY);

	unsigned char* data;
	int width;
	int height;
};