#include "World.h"

World::World(const RectI & screenRect)
	:
	car(VecF2(400.f, 300.f), RIGHT, rockets),
	player(car),
	screenRect(screenRect),
	mapRect(map.getRect()),
	ufo(VecF2(500.f,700.f),rng)
{
	bgm.Play(1.f, 0.35f);
}

World::~World()
{
	for (auto r : rockets)delete r;
	rockets.clear();
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
		if (!ufo.isDead() && rockets[i] != nullptr && colliding(*rockets[i], ufo))
		{
			indices.push_back(i);
			sndBoom.Play();
			const VecI2 rocketPos = rockets[i]->getPosConst();

			animations.push_back(rockets[i]->getBoomAnim());

			const float attack = rockets[i]->getAttack();
			if (ufo.damage(attack))
			{
				makeBigBoom(10, rocketPos, 70, rng, animations);

				animations.emplace_back(rocketPos, "sprites\\big_fire.bmp", 4, 30, 35, true);
			}
		}

		else if (!rockets[i]->getHitbox().isOverlappingWith(mapRect))
			indices.push_back(i);

	}

	for (int i : indices)
	{
		delete rockets[i];
		remove_element(rockets, i);
	}

	remove_erase_if(animations, [](Animation& a) {return a.isEnded(); });

	//car bouncing of map bounds
	if (!collidingWithBounds(car,mapRect))
		car.bounceBack();

	//car bouncing of ufo
	if (!ufo.isDead() && colliding(car, ufo))
		car.bounceBack(true);
	//camera following car
	const VecF2 center = VecF2( 400.f,300.f ) + camera.pos;

	////FIXME: too fast car, error here
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
