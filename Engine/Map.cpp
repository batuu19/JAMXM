#include "Map.h"


void Map::draw(Graphics & gfx, VecF2 cameraPos) const
{
	gfx.drawSprite(pos - cameraPos, mapSprite);
	mapAI.draw(gfx,cameraPos);
}

const RectI& Map::getRect() const
{
	return mapSprite.getRect();
}

Map::AI::AI(std::string filename)
{
	std::ifstream file(filename);
	std::string s;

	file >> s >> width;

	file >> s >> branch;

	int top, left, bottom, right;
	file >> s >> top >> left >> bottom >> right;
	bounds = { left,right,top,bottom };

	float x, y;
	while (!file.eof())
	{
		file >> x >> y >> s;
		points.emplace_back(x,1600 - y);
	}
}

void Map::AI::draw(Graphics & gfx,VecF2 cameraPos) const
{
	for (auto p : points)
	{
		p -= cameraPos;
		if (gfx.getScreenRect().getExpanded(-width).contains(p))
			gfx.drawRect(Rect<int>::fromCenter(p, width, 10), Colors::Red);
	}
}
