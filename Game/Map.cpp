#include "Map.h"


Map::Map(int mapNumber)
	:
	//mapSprite({DEBUG_MAP_SPRITE}),
	mapSprite(getMapImageFilename(mapNumber))

{
}

void Map::draw(Graphics & gfx, const VecF2& cameraPos) const
{
	gfx.drawSprite(pos - cameraPos, mapSprite);
	//mapAI.draw(gfx,cameraPos);
	//hitbox.testDraw(gfx, cameraPos,Colors::White);
}

const RectI& Map::getRect() const
{
	return mapSprite.getRect();
}

const VecI2 Map::getCarStartPos() const
{
	return { 400,300 };
}

const int Map::getCarStartDirection() const
{
	return RIGHT;
}

