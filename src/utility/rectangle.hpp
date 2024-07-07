#pragma once


class Rectangle
{
public:
	Rectangle(int width, int height);
	~Rectangle();
	void insertData(unsigned char* inputData, int inputWidth, int inputHeight, int posX, int posY);
	bool canFit(int inputWidth, int inputHeight, int posX, int posY);

private:
	int width;
	int height;
	unsigned char* data;
};