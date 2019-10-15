#pragma once


enum TileType
{
	GRASS, //0
	ROAD, //1
	UNKNOWN //last
};

class Tile
{
public:
	Tile();
	Tile(int raw);


private:
	TileType type;
	int xCoord = 0;
	int yCoord = 0;

};

