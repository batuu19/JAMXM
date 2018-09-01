#pragma once
#include "Car.h"
#include "BUtils.h"

class Player
{
public:
	Player(Car&);
	Player(const Player&) = delete;
	void update(float dt);
	void draw(Graphics&, VecF2 cameraPos) const;
	void handleInput(Keyboard&, Mouse&);
	const Car& getCarConst() const;

private:
	Car& car;
	bool shooting = false;
	Car::Speedup speedup = Car::Speedup::None;
};

class UI
{
public:
	void update(float dt);
	void draw(Graphics&,VecF2 cameraPos);
private:
	Player& player;
};
