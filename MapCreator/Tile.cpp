#include "Tile.h"

Tile::Tile()
	//TODO
	:Tile(0,Rect())
{}

Tile::Tile(int raw, Rect rect)
	:
	type((TileType)raw),
	rect(rect)
{}

Rect Tile::getRect() const
{
	return rect;
}

Scalar Tile::getScalar() const
{
	switch (type)
	{
	case GRASS:
		return Scalar(0, 255, 0);
	case ROAD:
		return Scalar(200);
	default:
		return Scalar(0);
	}
}
