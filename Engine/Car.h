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
#include <vector>
#include "Vec2.h"

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
	Vec2 pos;
	Vec2 vel;
	float speed;//speedup rate
	float maxVel;
	int dir = UP;

	std::vector<Surface> sprites;

	FrameTimer ft;
	//make it dependent on velocity
	float turnRate;
	float leftTurn = 0.0f;
	float rightTurn = 0.0f;
	int turnValue = 1;//how many directions at once

	void drawCar(Graphics &) const;
};