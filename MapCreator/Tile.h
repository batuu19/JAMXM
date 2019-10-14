#pragma once


enum TileType
{
	ROAD,
	GRASS,
};

class Tile
{
public:
	/*Tile()
	{
	}

	~Tile()
	{
	}*/

private:
	TileType type;
	int xCoord;
	int yCoord;

};

