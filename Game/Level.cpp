#include "Level.h"

Level::Level(const RectI& screenRect)
	:
	Level(screenRect, LevelConfig())
{}

Level::Level(const RectI& screenRect, LevelConfig levelConfig)
	:
	Scene(screenRect),
	map(std::make_shared<Map>(levelConfig.mapNumber)),
	camera(std::make_shared<Camera>()),
	rockets(std::make_shared<std::vector<std::shared_ptr<Rocket>>>()),
	animations(std::make_shared< std::vector<std::shared_ptr<Animation>>>()),
	car(std::make_shared<Car>(levelConfig.carStartPos, levelConfig.carStartDir, rockets, animations)),//memory problems with shared ptrs
	player(std::make_shared<Player>(car)),
	ui(std::make_shared<UI>(*player)),
	mapRect(map->getRect()),
	sndRaceStart({
		L"sound\\speech\\larry\\go_go_go.wav",
		L"sound\\speech\\larry\\let_the_carnage_begin.wav",
		L"sound\\speech\\larry\\lets_ride.wav"
		}),
	sndBoom(L"sound\\game\\explosion.wav"),
	sndEngine(L"sound\\game\\engine.wav"),
	sndAfterBoom({
		L"sound\\speech\\larry\\holy_transmission.wav",
		L"sound\\speech\\larry\\smashed.wav",
		L"sound\\speech\\larry\\terrific.wav",
		L"sound\\speech\\larry\\what_a_blow.wav",
		L"sound\\speech\\larry\\wipeout.wav"
		})
{
	dynamics.push_back(camera);
	//dynamics.push_back(car);
	dynamics.push_back(player);
	dynamics.push_back(ui);

	statics.push_back(map);
	//statics.push_back(car);
	statics.push_back(player);
	statics.push_back(ui);

	playables.push_back(player);

	camera->centerOn(*car, screenRect);
}

void Level::update(float dt)
{
	Scene::update(dt);
	std::vector<int> indices;
	for (int i = 0; i < rockets->size(); i++)
	{
		for (auto ufo : ufos)
		{
			if (colliding((*rockets)[i], ufo))
			{
				rockets->at(i)->kill();
				sndBoom.Play();
				animations->push_back(
					std::make_shared<Animation>((*rockets)[i]->getBoomAnim()));

				const VecI2 rocketPos = (*rockets)[i]->getPosConst();
				if (attack((*rockets)[i], ufo))
					//ufo killed
				{
					sndAfterBoom.Play(rng);
					player->scorePoints();
					auto booms = makeBigBoom(10, rocketPos, 70, rng);//TODO
					for (auto& a : booms)
						animations->push_back(std::make_shared<Animation>(std::move(a)));
					animations->push_back(
						std::make_shared<Animation>(rocketPos, "sprites\\big_fire.bmp", 4, 30, 35, true));
					//spawning new ufo
					ufo->kill();
					newUfoNeeded = true;
				}
			}
		}
		if (collidingWithBoundsFixed((*rockets)[i], mapRect))
			(*rockets)[i]->kill();

	}

	if (newUfoNeeded)
	{
		ufos.push_back(std::make_shared<UFO>(VecF2(float(xDist(rng)), float(yDist(rng))), rng));
		newUfoNeeded = false;
	}

	auto deadPred = [](std::shared_ptr<Entity> e) {return e->isDead(); };
	remove_erase_if(*rockets, deadPred);
	remove_erase_if(ufos, deadPred);

	remove_erase_if(*animations, [](std::shared_ptr<Animation> a) {return a->isEnded(); });

	//ufo damages car
	for (auto ufo : ufos)
		if (colliding(car, ufo) && attack(ufo, car))
			//TODO: make car invincible for few secends
			//car killed
		{

			player.reset();
			camera->centerOn(*car, screenRect);
			carDead = false;
		}
	//car bouncing of map bounds
	if (!collidingWithBounds(car, mapRect))
		car->bounceBack();

	////car bouncing of ufo
	//for (auto ufo : ufos)
	//	if (!ufo->isDead() && colliding(car, ufo))
	//		car->bounceBack(true);
	//camera following car
	const VecF2 center = VecF2(400.f, 300.f) + camera->pos;

	if (getDistanceSq(*car, center) * car->getVelConst().getLengthSq() > 800000000.f)
		camera->move((car->getPosConst() - center).getNormalized());
	//don't let camera off map
	if (camera->pos.x < mapRect.left)camera->pos.x = (float)mapRect.left;
	if (camera->pos.x + screenRect.right > mapRect.right)camera->pos.x = (float)(mapRect.right - screenRect.right);
	if (camera->pos.y < mapRect.top)camera->pos.y = (float)mapRect.top;
	if (camera->pos.y + screenRect.bottom > mapRect.bottom)camera->pos.y = (float)(mapRect.bottom - screenRect.bottom);

	//ufo physics
	for (auto ufo : ufos)
		if (!collidingWithBounds(ufo, mapRect))
			ufo->bounceBack();
	
	for (auto& a : *animations)
		a->update(dt);

}

void Level::draw(Graphics& gfx, const VecF2& cameraPos)
{
	Scene::draw(gfx,camera->pos);
	for (auto& a : *animations)
		a->draw(gfx, camera->pos);
}

void Level::handleInput(Keyboard::Event e)
{
	Scene::handleInput(e);
	if (e.IsPress())
	{
		switch (e.GetCode())
		{
		case 'R':
			reset();
			break;
		default:
			break;
		}
	}
}

void Level::reset()
{
}

const Map& Level::getMapConst() const
{
	return *map;
}

const Player& Level::getPlayerConst() const
{
	return *player;
}
