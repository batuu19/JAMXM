#pragma once

#include "Graphics.h"
#include "Directions.h"
#include "FrameTimer.h"
#include "Config.h"
#include <math.h>
#include <algorithm>
#include <assert.h>
#include <sstream>
#include "Surface.h"

class Car
{

public:
	Car(Config&);

	void turnLeft();
	void turnRight();
	void update();
	void speedup(bool faster = true);
	void draw(Graphics&) const;

	std::string getDebugInfo() const;
private:
	float xPos, yPos;
	float velocity;
	float speed;//speedup rate
	float maxVel;
	int dir = UP;

	Surface sprites;

	FrameTimer ft;
	float turnRate;
	float leftTurn = 0.0f;
	float rightTurn = 0.0f;
	int turnValue = 1;//how many directions at once

	void drawCar(Graphics &) const;
};