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
	car(std::make_shared<Car>()),
	player(std::make_shared<Player>(car)),
	carController(std::make_shared<CarController>(car, *map,rockets,animations)),
	ui(std::make_shared<UI>(carController)),
	mapRect(map->getRect()),
	sndRaceStart({
		L"sound\\speech\\larry\\go_go_go.wav",
		L"sound\\speech\\larry\\let_the_carnage_begin.wav",
		L"sound\\speech\\larry\\lets_ride.wav"
		}),
	sndBoom(L"sound\\game\\explosion.wav"),
	//sndEngine(L"sound\\game\\engine.wav"),
	sndAfterBoom({
		L"sound\\speech\\larry\\holy_transmission.wav",
		L"sound\\speech\\larry\\smashed.wav",
		L"sound\\speech\\larry\\terrific.wav",
		L"sound\\speech\\larry\\what_a_blow.wav",
		L"sound\\speech\\larry\\wipeout.wav"
		}),
	xDist(mapRect.left + 200, mapRect.right - 200),
	yDist(mapRect.top + 200, mapRect.bottom - 200)
{
	//add animations here
	dynamics.push_back(camera);
	//dynamics.push_back(car);
	dynamics.push_back(carController);
	dynamics.push_back(ui);

	statics.push_back(map);
	//statics.push_back(car);
	statics.push_back(carController);
	statics.push_back(ui);

	playables.push_back(carController);
	camera->centerOn(*carController, screenRect);
	auto ufo = std::make_shared<UFO>(VecF2((float)xDist(rng),(float)yDist(rng)), rng);
	ufos.push_back(ufo);
	dynamics.push_back(ufo);
	statics.push_back(ufo);
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
				auto boomAnim = std::make_shared<Animation>((*rockets)[i]->getBoomAnim());
				animations->push_back(boomAnim);

				const VecI2 rocketPos = (*rockets)[i]->getPosConst();
				if (attack((*rockets)[i], ufo))
					//ufo killed
				{
					sndAfterBoom.Play(rng);
					carController->scorePoints();
					auto booms = makeBigBoom(10, rocketPos, 70, rng);//TODO
					for (auto& boom : booms)
					{
						auto anim = std::make_shared<Animation>(std::move(boom));
						animations->push_back(anim);
					}
					auto bigFire = std::make_shared<Animation>(rocketPos, "sprites\\big_fire.bmp", 4, 30, 35, true);
					animations->push_back(bigFire);
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
		auto nextUFO = std::make_shared<UFO>(VecF2(float(xDist(rng)), float(yDist(rng))), rng);
		ufos.push_back(nextUFO);
		dynamics.push_back(nextUFO);
		statics.push_back(nextUFO);
		newUfoNeeded = false;
	}

	auto deadPred = [](std::shared_ptr<Entity> e) {return e->isDead(); };
	remove_erase_if(*rockets, deadPred);
	remove_erase_if(ufos, deadPred);

	remove_erase_if(*animations, [](std::shared_ptr<Animation> a) {return a->isEnded(); });

	//ufo damages car
	for (auto ufo : ufos)
		if (colliding(carController, ufo) && attack(ufo, carController))
			//TODO: make car invincible for few secends
			//car killed
		{

			player.reset();
			camera->centerOn(*carController, screenRect);
			carDead = false;
		}
	//car bouncing of map bounds
	if (!collidingWithBounds(carController, mapRect))
		carController->bounceBack();

	////car bouncing of ufo
	//for (auto ufo : ufos)
	//	if (!ufo->isDead() && colliding(car, ufo))
	//		car->bounceBack(true);
	//camera following car
	const VecF2 center = VecF2(400.f, 300.f) + camera->pos;

	if (getDistanceSq(*carController, center) * carController->getVelConst().getLengthSq() > 800000000.f)
		camera->move((carController->getPosConst() - center).getNormalized());
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
	Scene::draw(gfx, camera->pos);
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
			carController->reset();
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
