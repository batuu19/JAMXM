#include "Map.h"

void Map::generateFile(std::string inputFile, std::string outputFile)
{
	loadFromFile(inputFile);
	//magic
	saveToFile(outputFile);
}

void Map::loadFromFile(std::string inputFile)
{
	std::ifstream file;
	file.open(inputFile);
	int value;
	while (!file.eof()) 
	{
		value = file.get() - '0';
		if (isValidForTile(value)) 
		{
			tiles.push_back(value);
		}
	}
}

void Map::saveToFile(std::string outputFile)
{
}

bool Map::isValidForTile(int value)
{
	for (int i = 0; i < UNKNOWN; i++)
	{
		if (value == i)return true;
	}
	return false;
}
