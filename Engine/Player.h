#pragma once
#include "Car.h"

class Player
{
public:
	Player(Car car);
	void update(float dt);
	void draw(Graphics &) const;
	const RectF& getRect() const;
	void handleInput(Keyboard&, Mouse&);

private:
	Car car;

};
