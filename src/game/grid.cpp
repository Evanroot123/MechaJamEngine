#include "grid.hpp"
#include <cstdlib>

Grid::Grid(int width, int height, int tileWidth, int tileHeight, Texture* texture) 
	: width(width), height(height), tileWidth(tileWidth), tileHeight(tileHeight), texture(texture)
{
	data = new Tile[width * height];
	initializeData();
}

Grid::~Grid()
{
	delete[] data;
}

void Grid::initializeData()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			//TileType type = rand() % 10 ? TileType::Wall : TileType::Empty;
			TileType type = TileType::Empty;
			data[i * height + j].type = type;
		}
	}
}