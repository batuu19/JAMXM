#pragma once
#include<vector>
#include "Tile.h"
#include "OpenCV.h"

class Map
{
public:
	static constexpr int x = 10;
	static constexpr int y = 10;


private:
	std::vector<Tile> tiles;
};