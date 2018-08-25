#include "World.h"

World::World(const RectI & screenRect)
	:
	car( VecF2(150.f,150.f), RIGHT ,rockets),
	player(car),
	wreck(VecF2(300.f, 300.f), "sprites\\wreck_65x137.bmp", 65, 137, 1, 1)
{
	bgm.Play(1.f, 0.35f);
}

void World::handleInput(Keyboard & kbd, Mouse & mouse)
{
	player.handleInput(kbd, mouse);

	if (kbd.KeyIsPressed('R'))
	{
		animations.clear();
	}
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
			const VecI2 rocketPos = rockets[i].getPosConst();
			animations.emplace_back(rocketPos, "sprites\\big_explosion_336x55.bmp", 6, 336/6, 55);
			animations.emplace_back(rocketPos, "sprites\\small_fire_80x24.bmp", 4, 20, 24, true);
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
