#include "Map.h"

Map::Map()
	:
	Map(DEFAULT_TILE_SIZE, DEFAULT_TILE_SIZE, DEFAULT_MAP_COLS_ROWS, DEFAULT_MAP_COLS_ROWS)
{}

Map::Map(int tileWidth, int tileHeight, int cols, int rows)
	:
	tileRect(0, 0, tileWidth, tileHeight),
	cols(cols),
	rows(rows)
{
	tiles.reserve((size_t)cols*(size_t)rows);
}

void Map::generateFile(std::string inputFile, std::string outputFile)
{
	loadFromFile(inputFile);
	//magic

	cv::Mat image(tileRect.width * rows, tileRect.height * cols, CV_8UC3, Scalar(0, 0, 0));


	std::vector<Point> pts(4);
	std::vector<std::vector<Point>> vpts;
	for (auto& tile : tiles) {
		auto r = tile.getRect();
		pts.clear();
		vpts.clear();
		pts.push_back({ r.x,r.y });;
		pts.push_back({ r.x + r.width,r.y });
		pts.push_back({ r.x + r.width,r.y + r.height });
		pts.push_back({ r.x,r.y + r.height });
		vpts.push_back(pts);
		//rectangle(image, tile.getRect(), tile.getScalar());
		fillPoly(image, vpts, tile.getScalar());
		
	}

	cv::imwrite(outputFile, image);

	//saveToFile(outputFile);
}

void Map::loadFromFile(std::string inputFile)
{
	std::ifstream file;
	file.open(inputFile);
	int value;
	Rect tRect(tileRect);
	int count = 0;
	while (!file.eof())
	{

		value = file.get() - '0';
		if (isValidForTile(value)) {
			tiles.push_back({ value,tRect });
			count++;
			if (count % cols == 0 && count != 0) {//end of row
				tRect.x = 0;
				tRect.y += tRect.width;
			}
			else {
				tRect.x += tRect.height;
			}
		}
	}
}

bool Map::isValidForTile(int value)
{
	for (int i = 0; i < UNKNOWN; i++)
	{
		if (value == i)return true;
	}
	return false;
}
