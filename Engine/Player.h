#pragma once
#include "Car.h"

class Player
{
public:
	Player(Car& car);
	void update(float dt);
	void draw(Graphics &) const;
	const RectF& getRect() const;
	void handleInput(Keyboard&, Mouse&);
	const Car& getCarConst() const;

private:
	Car& car;
	Car::TurnDirection nextTurn = Car::TurnDirection::None;
	bool shooting = false;
	Car::Speedup speedup = Car::Speedup::None;

};
