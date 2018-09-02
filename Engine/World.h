#pragma once
#include "BMath.h"
#include "Player.h"
#include "Entity.h"
#include "Map.h"
#include "Animation.h"
#include "BUtils.h"
#include "Camera.h"
#include "UFO.h"
class World
{
public:
	World(const RectI& screenRect);
	World(const World&) = delete;
	World& operator=(const World&) = delete;
	~World();
	void handleInput(Keyboard&, Mouse&);
	void update(float dt);
	void draw(Graphics&) const;
	const Map& getMapConst() const;
	const Player& getPlayerConst() const;
private:
	Map map;
	RectI screenRect;
	RectI mapRect;
	mutable std::mt19937 rng = std::mt19937(std::random_device{}());
	mutable std::uniform_int_distribution<int> xDist, yDist;
	Camera camera;
	std::vector<Rocket*> rockets;
	Car* car = nullptr;
	Player player;
	std::vector<Animation> animations;
	UFO* ufo = nullptr;

	Sound bgm = Sound(L"sound\\music\\music.wav",Sound::LoopType::AutoFullSound);
	bool musicPlaying = true;
	Sound sndBoom = Sound(L"sound\\game\\explosion.wav");

};