#pragma once


enum TileType
{
	GRASS = 0,
	ROAD = 1,
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
	Tile(int raw);

private:
	TileType type;
	int xCoord = 0;
	int yCoord = 0;

};

