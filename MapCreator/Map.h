#pragma once
#include<vector>
#include<iostream>
#include<fstream>

#include "OpenCV.h"

#include "Tile.h"

constexpr int VALUE_BREAK_LINE = 10;
constexpr int DEFAULT_TILE_SIZE = 100;
constexpr int DEFAULT_MAP_COLS_ROWS = 5;

using namespace cv;

class Map
{
public:
	Map();
	Map(int tileWidth, int tileHeight, int cols, int rows);

	void generateFile(std::string inputFile, std::string outputFile);
private:
	Rect tileRect;
	int cols, rows;
	std::vector<Tile> tiles;
	std::vector<int> values;

	void loadFromFile(std::string inputFile);
	bool isValidForTile(int value);
};