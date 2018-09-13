#include "Map.h"


Map::Map(int mapNumber)
	:
	mapSprite(getMapImageFilename(mapNumber)),
	mapAI(mapNumber)

{
	std::ifstream in(getMapHitboxFilename(mapNumber), std::ios::binary);
	if (!in.good())return;
	std::vector<VecI2> points;
	char data;
	while (in.get(data))
	{
		for (int i = 2; i >= 0; i--)
		{
			if (data >> (i * 4))
			{
				int x, y;
				int val = (int)in.tellg() * 2 + i;
				y = val / 800;
				x = val % 1600;
				points.emplace_back(x, y);

			}
		}
	}
	hitbox = { points };
}

void Map::draw(Graphics & gfx, VecF2 cameraPos) const
{
	gfx.drawSprite(pos - cameraPos, mapSprite);
	mapAI.draw(gfx,cameraPos);
}

const RectI& Map::getRect() const
{
	return mapSprite.getRect();
}

Hitbox Map::getHitbox() const
{
	return hitbox;
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

Map::AI::AI(int mapNumber)
	:
	AI(getAIFilename(mapNumber))
{
}

void Map::AI::draw(Graphics & gfx,VecF2 cameraPos) const
{
	auto draw = [&](VecF2 p,Color c = Colors::Red)
	{
		gfx.drawRect(Rect<int>::fromCenter(p, width, 10), c);
	};
	for (auto& p : points)
	{
		draw(p - cameraPos);
	}
	draw(points[0] - cameraPos, Colors::Yellow);
	
}
