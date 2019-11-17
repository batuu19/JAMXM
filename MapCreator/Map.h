#pragma once
#include<vector>
#include<iostream>
#include<fstream>
#include<random>

#include "OpenCV.h"

#include "Tile.h"

constexpr int VALUE_BREAK_LINE = 10;
constexpr int DEFAULT_TILE_SIZE = 5;
constexpr int DEFAULT_MAP_COLS_ROWS = 5;
constexpr int DEFAULT_MIN_COLS_ROWS = 40;
constexpr int DEFAULT_MAX_COLS_ROWS = 50;

using namespace cv;

class Map
{
public:
	Map();
	Map(int tileWidth, int tileHeight, int cols, int rows);

	void generateFile(std::string inputFile, std::string outputFile);
private:
	Rect tileRect;
	int cols, rows,tileSize;
	std::vector<Tile> tiles;
	std::vector<int> values;
	std::mt19937 rng = std::mt19937(std::random_device{}());
	std::uniform_real_distribution<double> percentageDist;

	void loadFromFile(std::string inputFile);
	bool isValidForTile(int value);
	void drawTile(Mat& image, Point tile, Vec3b color);
	std::vector<Point> getPointsFromRect(const Rect& rect);
	std::vector<Point> addExtraToLine(Point p1, Point p2);
};