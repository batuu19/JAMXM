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
	//~Level();
	void update(float dt) override;
	void draw(Graphics&, const VecF2& cameraPos) const override;
	void handleInput(Keyboard::Event) override;
public:
	void reset();
	const Map& getMapConst() const;
	const Player& getPlayerConst() const;
private://objects
	std::shared_ptr<Map> map;
	std::shared_ptr<Camera> camera;
	std::shared_ptr<Car> car;
	std::shared_ptr<Player> player;
	std::shared_ptr<UI> ui;
	std::shared_ptr<std::vector<std::shared_ptr<Rocket>>> rockets;
	std::vector<std::shared_ptr<UFO>> ufos;
	std::shared_ptr<std::vector<std::shared_ptr<Animation>>> animations;
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
