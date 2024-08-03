#pragma once

#include "texture.hpp"

class GameObject
{
public:
	GameObject(int posX, int posY, Texture* texture);
	int posX, posY;
	int sizeX, sizeY;
	Texture* texture;
};