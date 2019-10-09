#include "Map.h"



Map::Map(Graphics & gfx)
	:
	gfx(gfx),
	mapSprite(gfx.ScreenWidth,gfx.ScreenHeight)
{
}

Map::Map(const Config & config, Graphics & gfx)
	:
	gfx(gfx),
	mapSprite(config.getMapFilename())
{
}


void Map::draw()
{
	gfx.drawSpriteNonChroma(0, 0, mapSprite);
}
