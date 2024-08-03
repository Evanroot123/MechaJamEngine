#pragma once
#include <map>
#include <glm.hpp>
#include <texture.hpp>

enum TileType
{
	Empty,
	Wall
};

struct Tile
{
	TileType type;
	bool isOccupied;
};

class Grid
{
public:
	Grid(int width, int height, int tileWidth, int tileHeight, Texture* texture);
	~Grid();
	void initializeData();
	Tile* at(int x, int y) const { return &data[y * width + x]; }

	int width;
	int height;
	int tileWidth;
	int tileHeight;

	Texture* texture;
	Tile* data;
	std::map<TileType, glm::vec2> tileTypeToTexPos;
};