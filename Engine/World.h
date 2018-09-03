#pragma once
#include "BMath.h"
#include "Player.h"
#include "Entity.h"
#include "Map.h"
#include "Animation.h"
#include "BUtils.h"
#include "ContainerUtils.h"
#include "PhysicsUtils.h"
#include "Camera.h"
#include "UFO.h"
#include <exception>
class World
{
public:
	World(const RectI& screenRect);
	World(const World&) = delete;
	World& operator=(const World&) = delete;
	~World();
	void handleInput(Keyboard::Event);
	void update(float dt);
	void draw(Graphics&) const;
	void reset();
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
	Car* car = new Car(VecF2(400.f, 300.f), RIGHT, rockets);
	Player player;
	std::vector<Animation> animations;
	std::vector<UFO*> ufos;
	UI ui;
	Sound bgm = Sound(L"sound\\music\\music.wav",Sound::LoopType::AutoFullSound);
	bool musicPlaying = true;
	Sound sndBoom = Sound(L"sound\\game\\explosion.wav");

	bool newUfoNeeded = false;
	bool carDead = false;
};