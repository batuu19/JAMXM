#include "World.h"

World::World(const RectI& screenRect)
	:
	screenRect(screenRect)
{}


void World::handleInput(Keyboard::Event e)
{
	
}

void World::update(float dt)
{
	//camera.update(dt);
	//player.update(dt);
	//for (auto& a : animations)a.update(dt);
	//for (auto u : ufos)u->update(dt);
	//ui.update(dt);

	////rockets physics
	//std::vector<int> indices;
	//for (int i = 0; i < rockets.size(); i++)
	//{
	//	for (auto ufo : ufos)
	//	{
	//		if (colliding(rockets[i], ufo))
	//		{
	//			rockets[i]->kill();
	//			sndBoom.Play();
	//			animations.push_back(rockets[i]->getBoomAnim());

	//			const VecI2 rocketPos = rockets[i]->getPosConst();
	//			if (attack(rockets[i], ufo))
	//				//ufo killed
	//			{
	//				sndAfterBoom.Play(rng);
	//				player.scorePoints();
	//				makeBigBoom(10, rocketPos, 70, rng, animations);
	//				animations.emplace_back(rocketPos, "sprites\\big_fire.bmp", 4, 30, 35, true);
	//				//spawning new ufo
	//				ufo->kill();
	//				newUfoNeeded = true;
	//			}
	//		}
	//	}
	//	if (collidingWithBoundsFixed(rockets[i], mapRect))
	//		rockets[i]->kill();

	//}

	//if (newUfoNeeded)
	//{
	//	ufos.push_back(new UFO(VecF2(float(xDist(rng)), float(yDist(rng))), rng));
	//	newUfoNeeded = false;
	//}
	//cleanDead(rockets);
	//cleanDead(ufos);

	//remove_erase_if(animations, [](Animation& a) {return a.isEnded(); });

	////ufo damages car
	//for (auto ufo : ufos)
	//	if (colliding(car, ufo) && attack(ufo, car))
	//		//TODO: make car invincible for few secends
	//		//car killed
	//	{

	//		player.reset();
	//		camera.centerOn(*car, screenRect);
	//		carDead = false;
	//	}
	////car bouncing of map bounds
	//if (!collidingWithBounds(car, mapRect))
	//	car->bounceBack();

	//////car bouncing of ufo
	////for (auto ufo : ufos)
	////	if (!ufo->isDead() && colliding(car, ufo))
	////		car->bounceBack(true);
	////camera following car
	//const VecF2 center = VecF2(400.f, 300.f) + camera.pos;

	//if (getDistanceSq(*car, center) * car->getVelConst().getLengthSq() > 800000000.f)
	//	camera.move((car->getPosConst() - center).getNormalized());
	////don't let camera off map
	//if (camera.pos.x < mapRect.left)camera.pos.x = (float)mapRect.left;
	//if (camera.pos.x + screenRect.right > mapRect.right)camera.pos.x = (float)(mapRect.right - screenRect.right);
	//if (camera.pos.y < mapRect.top)camera.pos.y = (float)mapRect.top;
	//if (camera.pos.y + screenRect.bottom > mapRect.bottom)camera.pos.y = (float)(mapRect.bottom - screenRect.bottom);

	////ufo physics
	//for (auto ufo : ufos)
	//	if (!collidingWithBounds(ufo, mapRect))
	//		ufo->bounceBack();


	////testing map
	///*carOnRoad = map->getHitbox().contains(car->getHitbox());
	//if (!carOnRoad)car->bounceBack();*/


}

void World::draw(Graphics& gfx) const
{
	/*map->draw(gfx, camera.pos);
	player.draw(gfx, camera.pos);
	for (auto& a : animations)a.draw(gfx, camera.pos);
	for (auto u : ufos)if (!u->isDead())u->draw(gfx, camera.pos);
	ui.draw(gfx, camera.pos);*/


	//if (carOnRoad)gfx.drawRect({ car->getPosConst() - camera.pos,30,30 }, Colors::Black);
}
