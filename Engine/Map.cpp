#include "Map.h"

void Map::draw(Graphics& gfx) const
{
	draw(gfx, { 0.f,0.f });
}

void Map::draw(Graphics & gfx, VecF2 cameraPos) const
{
	gfx.drawSprite(pos - cameraPos, mapSprite);
}

const RectI& Map::getRect() const
{
	return mapSprite.getRect();
}
