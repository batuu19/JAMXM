#pragma once

#include "Graphics.h"
#include "Directions.h"
#include "FrameTimer.h"
#include "Config.h"
#include <math.h>
#include <algorithm>
#include <assert.h>
#include <sstream>

class Car
{

public:
	Car(Config&);
	Car (const Car&);
	Car& operator=(const Car&) = delete;
	~Car();

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
	Color c;
	int width;
	int height;

	Color* pPixels = nullptr;

	FrameTimer ft;
	float turnRate;
	float leftTurn = 0.0f;
	float rightTurn = 0.0f;
	int turnValue = 1;//how many directions at once

	void drawCar(Graphics &) const;
};