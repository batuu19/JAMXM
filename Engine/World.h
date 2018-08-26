#pragma once
#include "BMath.h"
#include "Player.h"
#include "Entity.h"
#include "Map.h"
#include "Animation.h"
#include "BUtils.h"
#include "Camera.h"
class World
{
public:
	World(const RectI& screenRect);
	World(const World&) = delete;
	void handleInput(Keyboard&, Mouse&);
	void update(float dt);
	void draw(Graphics&) const;
	const Map& getMapConst() const;
	const Player& getPlayerConst() const;
	const Entity& getWreckConst() const;
private:
	Camera camera;
	Map map;
	std::vector<Rocket> rockets;
	Car car;
	Player player;
	Entity wreck;
	std::vector<Animation> animations;

	Sound bgm = Sound(L"sound\\music\\music.wav",Sound::LoopType::AutoFullSound);
	bool musicPlaying = true;
	Sound sndBoom = Sound(L"sound\\game\\explosion.wav");

	RectI screenRect;
	RectI mapRect;
};