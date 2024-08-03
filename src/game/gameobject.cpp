#include "gameobject.hpp"

GameObject::GameObject(int posX, int posY, Texture* texture) : posX(posX), posY(posY), texture(texture)
{
	sizeX = texture->width;
	sizeY = texture->height;
}
