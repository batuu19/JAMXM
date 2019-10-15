#include "Tile.h"

Tile::Tile()
	:Tile(0)
{}

Tile::Tile(int raw)
{
	type = (TileType)raw;
}
