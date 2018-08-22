#include "World.h"

World::World(const RectI & screenRect)
	:
	player({ VecF2(150.f,150.f), RIGHT }),
	wreck(VecF2(650.f, 300.f), "sprites\\wreck.bmp", 80, 140, 1, 1)
{
}

void World::handleInput(Keyboard & kbd, Mouse & mouse)
{
	player.handleInput(kbd, mouse);
}

void World::update(float dt)
{
	player.update(dt);
}

void World::draw(Graphics & gfx) const
{
	map.draw(gfx);
	player.draw(gfx);
	wreck.draw(gfx);
}

const Map & World::getMapConst() const
{
	return map;
}

const Player & World::getPlayerConst() const
{
	return player;
}

const Entity & World::getWreckConst() const
{
	return wreck;
}
