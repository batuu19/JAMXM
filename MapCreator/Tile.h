#pragma once

#include <opencv/cv.h>
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
	cv::Rect rect;

};

