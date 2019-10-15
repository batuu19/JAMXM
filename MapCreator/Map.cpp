#include "Map.h"

void Map::generateFile(std::string inputFile, std::string outputFile)
{
	loadFromFile(inputFile);
	//magic

	cv::Mat image;
	image.create(x * 100, y * 100, CV_8UC3);

	cv::line(image, cv::Point(0, 0), cv::Point(100, 200), cv::Scalar(255, 0, 0));

	cv::imwrite(outputFile, image);
	


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
			tiles.push_back(value);
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
