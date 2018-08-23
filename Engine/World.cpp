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
	for (auto& a : animations)a.update(dt);

	auto pred = [this](Rocket& r) {return r.getHitbox().IsOverlappingWith(wreck.getHitbox()); };
	std::vector<int> indices;
	for (int i = 0; i < rockets.size(); i++)
	{
		if (pred(rockets[i]))
		{
			indices.push_back(i);
			sndBoom.Play();
			animations.emplace_back(rockets[i].getPosConst(), "sprites\\explosion.bmp", 6, 40, 40);
		}
	}

	for (int i : indices)rockets.erase(rockets.begin() + i);

	remove_erase_if(animations, [](Animation a) {return a.isEnded(); });
}

void World::draw(Graphics & gfx) const
{
	map.draw(gfx);
	wreck.draw(gfx);
	player.draw(gfx);
	for (auto a : animations)a.draw(gfx);
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
