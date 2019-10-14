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
	do
	{
		for (int i = 0; i < 4; i++)
		{
			value = file.get() - '0';
			values.push_back(value);
		}
	} while (file.get() != -1);
}

void Map::saveToFile(std::string outputFile)
{
}
