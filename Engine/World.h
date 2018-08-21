#pragma once
#include "BMath.h"
#include "Player.h"
#include "Entity.h"
#include "Map.h"
#include "Sound.h"
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
	Player player;
	Entity wreck;

	Sound bgm = Sound(L"sound\\music\\music.wav");
};