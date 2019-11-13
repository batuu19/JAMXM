#pragma once
#include "Scene.h"
#include "Map.h"
#include "Player.h"
#include "Animation.h"
#include "UFO.h"
#include "LevelConfig.h"

class Level : public Scene
{
public:
	Level(const RectI& screenRect, LevelConfig levelConfig);
	Level(Level&) = delete;
	Level& operator=(Level&) = delete;
	~Level();
	void update(float dt) override;
	void draw(Graphics&, const VecF2& cameraPos) const override;
	void handleInput(Keyboard::Event) override;
public:
	void reset();
	const Map& getMapConst() const;
	const Player& getPlayerConst() const;
private://objects
	Map* map;
	Camera* camera;
	Car* car;
	Player* player;
	UI* ui;
	std::vector<Rocket*> rockets;
	std::vector<UFO*> ufos;
	std::vector<Animation> animations;
private://sound
	Sound sndRaceStart;
	Sound sndBoom;
	Sound sndEngine;
	Sound sndAfterBoom;
private:
	RectI mapRect;
	bool newUfoNeeded = false;
	bool carDead = false;
	mutable std::mt19937 rng = std::mt19937(std::random_device{}());
	mutable std::uniform_int_distribution<int> xDist, yDist;

};
