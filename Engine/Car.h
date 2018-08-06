#pragma once

#include "Graphics.h"
#include "Directions.h"
#include "FrameTimer.h"
#include <math.h>
#include <algorithm>

class Car
{

public:
	Car(int startX, int startY, Color c);

	void turnLeft();
	void turnRight();
	void update();
	void speedup(bool faster = true);
	void draw(Graphics& gfx) const;
private:
	float xPos, yPos;
	float velocity = 0.0f;
	float speed = 0.4f;;//speedup rate
	int dir = RIGHT;
	Color c;
	const int width = 25;
	const int height = 25;
	const float maxVel = 7.0f;

	FrameTimer ft;
	const float turnRate = 0.18f;
	float leftTurn = turnRate;
	float rightTurn = turnRate;
};