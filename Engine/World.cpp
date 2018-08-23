#include "World.h"

World::World(const RectI & screenRect)
	:
	car( VecF2(150.f,150.f), RIGHT ,rockets),
	player(car),
	wreck(VecF2(650.f, 300.f), "sprites\\wreck.bmp", 80, 140, 1, 1)
{
	bgm.Play(1.f, 0.35f);
}

void World::handleInput(Keyboard & kbd, Mouse & mouse)
{
	player.handleInput(kbd, mouse);
}

void World::update(float dt)
{
	player.update(dt);
	explosion.update(dt);

	auto pred = [this](Rocket& r) {return r.getHitbox().IsOverlappingWith(wreck.getHitbox()); };
	std::vector<int> indices;
	for (int i = 0; i < rockets.size(); i++)
	{
		if (pred(rockets[i]))
		{
			indices.push_back(i);
			sndBoom.Play();
			explosion.play(rockets[i].getPosConst());
		}
	}

	for (int i : indices)rockets.erase(rockets.begin() + i);
}

void World::draw(Graphics & gfx) const
{
	map.draw(gfx);
	wreck.draw(gfx);
	player.draw(gfx);
	explosion.draw(gfx);
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
