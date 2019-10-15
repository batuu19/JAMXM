#pragma once
#include<vector>
#include<iostream>
#include<fstream>

#include "Tile.h"
#include "OpenCV.h"

constexpr int VALUE_BREAK_LINE = 10;

class Map
{
public:
	static constexpr int x = 10;
	static constexpr int y = 10;

	void generateFile(std::string inputFile, std::string outputFile);
private:
	std::vector<Tile> tiles;
	std::vector<int> values;

	void loadFromFile(std::string inputFile);
	void saveToFile(std::string outputFile);
	bool isValidForTile(int value);
};