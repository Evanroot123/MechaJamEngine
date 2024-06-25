#pragma once

#include "texture.hpp"

class GameObject
{
public:
	int posX, posY;
	int sizeX, sizeY;
	Texture* texture;
};