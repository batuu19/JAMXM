#include "Level.h"

Level::Level(const RectI& screenRect,LevelConfig levelConfig)
	:
	Scene(screenRect),
	map(std::make_shared<Map>(levelConfig.mapNumber)),
	camera(std::make_shared<Camera>()),
	car(std::make_shared<Car>(levelConfig.carStartPos, levelConfig.carStartDir, rockets, animations)),
	player(std::make_shared<Player>(car)),
	ui(std::make_shared<UI>(*player)),
	mapRect(map->getRect())
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
}

void Level::draw(Graphics&, const VecF2& cameraPos) const
{
}

void Level::handleInput(Keyboard::Event)
{
}

void Level::reset()
{
}

const Map& Level::getMapConst() const
{
	// TODO: insert return statement here
}

const Player& Level::getPlayerConst() const
{
	// TODO: insert return statement here
}
