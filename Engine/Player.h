#pragma once
#include "Keyboard.h"
#include "Car.h"
#include "FrameTimer.h"

class Player
{
public:
	Player(Car & car);
	void update(Keyboard &);
	void draw(Graphics &);
private:
	Car car;
	
	FrameTimer ft;
	float leftTurn = 0.0f;
	float rightTurn = 0.0f;
	const float turnRate = 0.5f;

};
