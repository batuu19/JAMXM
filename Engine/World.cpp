#include "World.h"

World::World(const RectI & screenRect)
	:
	car(VecF2(400.f, 300.f), RIGHT, rockets),
	player(car),
	screenRect(screenRect),
	mapRect(map.getRect())
{
	bgm.Play(1.f, 0.35f);
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
	ufo.update(dt);

	//rockets exploding on wreck
	std::vector<int> indices;
	for (int i = 0; i < rockets.size(); i++)
	{
		int object = 0;
		if (!ufo.isDead() && colliding(rockets[i], ufo))object = 2;
		if (object > 0)
		{
			indices.push_back(i);
			sndBoom.Play();
			const VecI2& rocketPos = rockets[i].getPosConst();
			/*
			const int rocketType = rockets[i].getType(); 
			if (rocketType == 0)animations.emplace_back(rocketPos, "sprites\\small_explosion_240x40.bmp", 6, 240 / 6, 40);
			else if (rocketType == 1)animations.emplace_back(rocketPos, "sprites\\big_explosion_336x55.bmp", 6, 336 / 6, 55);
			if (object == 1)animations.emplace_back(rocketPos, "sprites\\small_fire_80x24.bmp", 4, 20, 24, true);*/

			const float attack = rockets[i].getAttack();
			switch (object)
			{
			case 2:
				if (ufo.damage(attack))
				{
					animations.emplace_back(rocketPos + VecF2{ 11.f, 27.f }, "sprites\\big_explosion_336x55.bmp", 6, 336 / 6, 55);
					animations.emplace_back(rocketPos + VecF2{ 3.f, 4.f}, "sprites\\big_explosion_336x55.bmp", 6, 336 / 6, 55);
					animations.emplace_back(rocketPos + VecF2{ 36.f, 11.f }, "sprites\\big_explosion_336x55.bmp", 6, 336 / 6, 55);
					animations.emplace_back(rocketPos + VecF2{ 32.f, 2.f }, "sprites\\big_explosion_336x55.bmp", 6, 336 / 6, 55);
					animations.emplace_back(rocketPos - VecF2{ 11.f, 27.f }, "sprites\\big_explosion_336x55.bmp", 6, 336 / 6, 55);
					animations.emplace_back(rocketPos - VecF2{ 3.f, 4.f }, "sprites\\big_explosion_336x55.bmp", 6, 336 / 6, 55);
					animations.emplace_back(rocketPos - VecF2{ 36.f, 11.f }, "sprites\\big_explosion_336x55.bmp", 6, 336 / 6, 55);
					animations.emplace_back(rocketPos - VecF2{ 32.f, 2.f }, "sprites\\big_explosion_336x55.bmp", 6, 336 / 6, 55);

					animations.emplace_back(rocketPos, "sprites\\big_fire.bmp", 4, 30, 35,true);
				}
				break;

			default:
				break;
			}
		}

		else if (!rockets[i].getHitbox().isOverlappingWith(mapRect))
			indices.push_back(i);

	}

	//for (int i : indices)rockets.erase(rockets.begin() + i);

	remove_erase_if(animations, [](Animation& a) {return a.isEnded(); });

	//car bouncing of map bounds
	if (!collidingWithBounds(car,mapRect))
		car.bounceBack();

	//car bouncing of ufo
	if (!ufo.isDead() && colliding(car, ufo))
		car.bounceBack(true);
	//camera following car
	const VecF2 center = VecF2( 400.f,300.f )  camera.pos;

	//FIXME: too fast car, error here
	if (getDistanceSq(car, center) * car.getVelConst().getLengthSq() > 800000000.f )
		camera.move((car.getPosConst() - center).getNormalized());
	//don't let camera off map
	if (camera.pos.x < mapRect.left)camera.pos.x = (float)mapRect.left;
	if (camera.pos.x + screenRect.right > mapRect.right)camera.pos.x = (float)(mapRect.right - screenRect.right);
	if (camera.pos.y < mapRect.top)camera.pos.y = (float)mapRect.top;
	if (camera.pos.y + screenRect.bottom > mapRect.bottom)camera.pos.y = (float)(mapRect.bottom - screenRect.bottom);

	//ufo physics
	if (!collidingWithBounds(ufo, mapRect))
		ufo.bounceBack();
}

void World::draw(Graphics & gfx) const
{
	map.draw(gfx, camera.pos);
	player.draw(gfx, camera.pos);
	for (auto& a : animations)a.draw(gfx, camera.pos);
	ufo.draw(gfx,camera.pos);

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
