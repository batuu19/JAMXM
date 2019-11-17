#include "Map.h"

Map::Map()
	:
	Map(DEFAULT_TILE_SIZE, DEFAULT_TILE_SIZE, DEFAULT_MAP_COLS_ROWS, DEFAULT_MAP_COLS_ROWS)
{}

Map::Map(int tileWidth, int tileHeight, int cols, int rows)
	:
	tileRect(0, 0, tileWidth, tileHeight),
	cols(cols),
	rows(rows),
	tileSize(5)
{
	tiles.reserve((size_t)cols * (size_t)rows);
}

void Map::generateFile(std::string inputFile, std::string outputFile)
{
	loadFromFile(inputFile);
	//magic

	//create rectangle
	std::uniform_int_distribution<int> rowDist(DEFAULT_MIN_COLS_ROWS, DEFAULT_MAX_COLS_ROWS);
	rows = rowDist(rng);
	cols = (int)((double)rows * 1.5);
	if (percentageDist(rng) < 0.4)
		std::swap(rows, cols);

	std::uniform_int_distribution<int> xDist(0, cols - 1);
	std::uniform_int_distribution<int> yDist(0, rows - 1);
	std::vector<std::vector<Rect>> roadTiles;


	Point nextPoint = { cols / 2,rows / 2 };


	Vec3b tileColor = { 0,255,0 };
	Vec3b defaultBackground = { 64,64,64 };
	Mat image(tileRect.width * rows, tileRect.height * cols, CV_8UC3, defaultBackground);
	Mat tileImage(rows, cols, CV_8UC3, defaultBackground);

	//draw inside rectangle
	int xPad = cols * 0.2;
	int yPad = rows * 0.2;
	//rectangle(tileImage, { xPad,yPad }, { cols - xPad,rows - yPad }, tileColor);
	std::vector<Point> pts, rectPts, extraPts;

	rectPts = getPointsFromRect(Rect(Point(xPad, yPad), Point(cols - xPad, rows - yPad)));
	pts.push_back(rectPts[0]);
	extraPts = addExtraToLine(rectPts[0], rectPts[1]);
	pts.insert(pts.end(), extraPts.begin(), extraPts.end());
	
	pts.push_back(rectPts[1]);

	extraPts = addExtraToLine(rectPts[1], rectPts[2]);

	pts.insert(pts.end(), extraPts.begin(), extraPts.end());
	pts.push_back(rectPts[2]);
	pts.push_back(rectPts[3]);

	extraPts = addExtraToLine(rectPts[3], rectPts[0]);

	pts.insert(pts.end(), extraPts.begin(), extraPts.end());

	polylines(tileImage, pts, true, tileColor);

	for (int y = 0; y < tileImage.rows; y++)
	{
		for (int x = 0; x < tileImage.cols; x++)
		{
			Vec3b color = tileImage.at<Vec3b>(Point(x, y));
			// set pixel
			drawTile(image, { x,y }, color);
		}
	}

	cv::imwrite(outputFile, image);
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

void Map::drawTile(Mat& image, Point tile, Vec3b color)
{
	rectangle(image, tile * tileSize, tile * tileSize + Point(tileSize, tileSize), color, CV_FILLED);
}

std::vector<Point> Map::getPointsFromRect(const Rect& rect)
{
	return std::vector<Point> {rect.tl(), rect.tl() + Point(rect.width, 0), rect.br(), rect.tl() + Point(0, rect.height)};
}

std::vector<Point> Map::addExtraToLine(Point p1, Point p2)
{
	if (p1.x == p2.x)//vertical line
	{
		std::uniform_int_distribution<int> yDist;
		bool down = true;
		if (p1.y < p2.y)
		{
			yDist = std::uniform_int_distribution<int>(p1.y, p2.y);
			down = true;
		}
		else if (p2.y < p1.y)
		{
			yDist = std::uniform_int_distribution<int>(p2.y, p1.y);
			down = false;
		}
		else return std::vector<Point>();
		int y1, y2;
		y1 = yDist(rng);
		y2 = yDist(rng);
		if (y1 > y2)
			std::swap(y1, y2);

		int width = 3;
		if (0.5 < percentageDist(rng))
			width *= -1;

		std::vector<Point> outPoints;

		outPoints.push_back({ p1.x,y1 });
		outPoints.push_back({ p1.x + width,y1 });
		outPoints.push_back({ p1.x + width,y2 });
		outPoints.push_back({ p1.x,y2 });

		if (!down)
			std::reverse(outPoints.begin(), outPoints.end());
		return outPoints;


	}
	else if (p1.y == p2.y)//horizontal line
	{
		std::uniform_int_distribution<int> xDist;
		bool right = true;
		if (p1.x < p2.x)
		{
			xDist = std::uniform_int_distribution<int>(p1.x, p2.x);
			right = true;
		}
		else if (p2.x < p1.x)
		{
			xDist = std::uniform_int_distribution<int>(p2.x, p1.x);
			right = false;
		}
		else return std::vector<Point>();
		int x1, x2;
		x1 = xDist(rng);
		x2 = xDist(rng);
		if (x1 > x2)
			std::swap(x1, x2);
		int height = 3;

		std::vector<Point> outPoints;

		outPoints.push_back({ x1,p1.y });
		outPoints.push_back({ x1,p1.y + height });
		outPoints.push_back({ x2,p1.y + height });
		outPoints.push_back({ x2,p1.y });

		if(!right)
			std::reverse(outPoints.begin(), outPoints.end());
		return outPoints;


	}
	else return std::vector<Point>();
}
