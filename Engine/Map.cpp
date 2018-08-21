#include "Map.h"

void Map::draw(Graphics& gfx) const
{
	gfx.drawSpriteNonChroma(0, 0, mapSprite);
}
