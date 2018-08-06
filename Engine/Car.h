#pragma once

#include "Graphics.h"
#include "Directions.h"
#include "FrameTimer.h"
#include "Config.h"
#include <math.h>
#include <algorithm>

class Car
{

public:
	Car(Config&);

	void turnLeft();
	void turnRight();
	void update();
	void speedup(bool faster = true);
	void draw(Graphics& gfx) const;
private:
	float xPos, yPos;
	float velocity;
	float speed;//speedup rate
	float maxVel;
	int dir = RIGHT;
	Color c;
	const int width = 25;
	const int height = 25;

	FrameTimer ft;
	float turnRate;
	float leftTurn;
	float rightTurn;
};