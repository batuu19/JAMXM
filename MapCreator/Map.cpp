#include "Map.h"

void Map::generateFile(std::string inputFile, std::string outputFile)
{
	loadFromFile(inputFile);
	//magic

	cv::Mat image(500, 500, CV_8UC3, cv::Scalar(0, 0, 255));

	cv::line(image, cv::Point(0, 0), cv::Point(100, 200), cv::Scalar(255, 0, 0));
	

	std::vector<cv::Point> pts = { {10,10},{10,20},{20,30},{40,50},{10,40} };

	std::vector<std::vector<cv::Point>> vpts;
	vpts.push_back(pts);

	cv::fillPoly(image, vpts, cv::Scalar(255, 0, 0));

	cv::imwrite(outputFile, image);

	//saveToFile(outputFile);
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
