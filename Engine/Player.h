#pragma once
#include "Keyboard.h"
#include "Car.h"
#include "FrameTimer.h"
#include "Debug.h"

class Player
{
public:
	Player(Car & car);
	void update(Keyboard &);
	void draw(Graphics &);
private:
	Car car;

};
