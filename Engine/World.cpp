#include "World.h"

World::World(const RectI & screenRect)
	:
	car(VecF2(400.f, 300.f), RIGHT, rockets),
	player(car),
	wreck(VecF2(300.f, 300.f), "sprites\\wreck_65x137.bmp", 65, 137, 1, 1),
	centerRect(300, 500, 200, 400)
{
	//bgm.Play(1.f, 0.35f);
}

void World::handleInput(Keyboard & kbd, Mouse & mouse)
{
	camera.handleInput(kbd);
	player.handleInput(kbd, mouse);

	//reseting
	if (kbd.KeyIsPressed('R'))
	{
		animations.clear();
		camera.pos = { 0.f,0.f };
	}
}

void World::update(float dt)
{
	camera.update(dt);
	player.update(dt);
	for (auto& a : animations)a.update(dt);

	//rockets exploding on wreck
	std::vector<int> indices;
	for (int i = 0; i < rockets.size(); i++)
	{
		if (checkCollision(rockets[i], wreck))
		{
			indices.push_back(i);
			sndBoom.Play();
			const VecI2 rocketPos = rockets[i].getPosConst();
			animations.emplace_back(rocketPos, "sprites\\big_explosion_336x55.bmp", 6, 336/6, 55);
			animations.emplace_back(rocketPos, "sprites\\small_fire_80x24.bmp", 4, 20, 24, true);
		}
	}

	for (int i : indices)rockets.erase(rockets.begin() + i);

	remove_erase_if(animations, [](Animation& a) {return a.isEnded(); });

	//car bouncing of wreck
	if (checkCollision(car, wreck))
	{
		car.bounceBack();
	}

	//camera following car
	const VecF2 center = VecF2( 400.f,300.f ) - camera.pos;
	if (getDistanceSq(car, center) * car.getVelConst().getLengthSq() > 800000000.f)
		camera.move((car.getPosConst() - center).getNormalized());

}

void World::draw(Graphics & gfx) const
{
	map.draw(gfx, camera.pos);
	wreck.draw(gfx, camera.pos);
	player.draw(gfx, camera.pos);
	for (auto& a : animations)a.draw(gfx, camera.pos);

	//gfx.drawRect(RectI::fromCenter({ 400,300 }, 10, 10),Colors::Red);
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
