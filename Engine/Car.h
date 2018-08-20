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
#include "BMath.h"
#include "SpriteContainer.h"
#include "Rocket.h"

//TODO: add collision using RectI
class Car
{

public:
	//TODO: without config
	Car(const Config&);

	void turnLeft();
	void turnRight();
	void update();
	void speedup(bool faster = true);
	void draw(Graphics&) const;
	void reset();

	void shoot();
	std::string getDebugInfo() const;
private:
	VecF2 pos;
	VecF2 vel;
	float speed;//speedup rate
	float maxVel;
	int dir;
	const Config& config;

	SpriteContainer sprites;

	FrameTimer turnTimer;
	//make it dependent on velocity
	float turnRate;
	float leftTurn = 0.f;
	float rightTurn = 0.f;
	int turnValue = 1;//how many directions at once

	void drawCar(Graphics &) const;

	std::vector<Rocket> rocketsFired;
	FrameTimer shootTimer;
	float shootRate = 0.1f;
	float lastShot = 0.f;
};