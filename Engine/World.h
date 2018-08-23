#pragma once
#include "BMath.h"
#include "Player.h"
#include "Entity.h"
#include "Map.h"
#include "Sound.h"
#include "Animation.h"
class World
{
public:
	World(const RectI& screenRect);
	void handleInput(Keyboard&, Mouse&);
	void update(float dt);
	void draw(Graphics&) const;
	const Map& getMapConst() const;
	const Player& getPlayerConst() const;
	const Entity& getWreckConst() const;
private:
	Map map;
	std::vector<Rocket> rockets;
	Car car;
	Player player;
	Entity wreck;
	Animation explosion = Animation("sprites\\explosion\\explosion.bmp",6,40,40);

	Sound bgm = Sound(L"sound\\music\\music.wav",Sound::LoopType::AutoFullSound);
	Sound sndBoom = Sound(L"sound\\game\\explosion.wav");
};