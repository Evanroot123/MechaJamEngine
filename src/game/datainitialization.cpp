#include "datainitialization.h"

void initializeTileMapTexturePos(Grid& grid)
{
	grid.tileTypeToTexPos[TileType::Empty] = glm::vec2{ 0,0 };
	grid.tileTypeToTexPos[TileType::Wall] = glm::vec2{ 0,0 };
}
