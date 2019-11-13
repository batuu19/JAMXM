#include "Level.h"

Level::Level(const RectI& screenRect,LevelConfig levelConfig)
	:
	Scene(screenRect),
	map(new Map(levelConfig.mapNumber)),
	camera(new Camera()),
	car(new Car(levelConfig.carStartPos, levelConfig.carStartDir, rockets, animations)),
	player(new Player(car)),
	ui(new UI(*player)),
	mapRect(map->getRect())
{
	camera->centerOn(*car, screenRect);
}

Level::~Level()
{
	delete ui;
	delete player;
	delete car;
	delete camera;
	delete map;
	cleanAndClear(rockets);
	cleanAndClear(ufos);
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
