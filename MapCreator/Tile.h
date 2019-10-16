#pragma once

#include "OpenCV.h"
using namespace cv;
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
	Tile(int raw,Rect rect);

	Rect getRect() const;
	Scalar getScalar() const;

private:
	TileType type;
	cv::Rect rect;

};

