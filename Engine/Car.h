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
#include "SpriteContainer.h"

class Car
{

public:
	//TODO: without config
	Car(Config&);

	void turnLeft();
	void turnRight();
	void update();
	void speedup(bool faster = true);
	void draw(Graphics&) const;
	void reset();

	std::string getDebugInfo() const;
private:
	Vec2 pos;
	Vec2 vel;
	float speed;//speedup rate
	float maxVel;
	int dir = UP;
	Config& config;

	SpriteContainer sprites;

	FrameTimer ft;
	//make it dependent on velocity
	float turnRate;
	float leftTurn = 0.0f;
	float rightTurn = 0.0f;
	int turnValue = 1;//how many directions at once

	void drawCar(Graphics &) const;

	//TODO: move that from there
	std::vector<Vec2> directionVec =
	{
		{ 0.0f,-1.0f },//up
		{ 1.0f,-2.0f },
		{ 1.0f,-1.0f },//up_right
		{ 2.0f,-1.0f },
		{ 2.0f,0.0f },//right
		{ 2.0f,1.0f },
		{ 1.0f,1.0f },//down_right
		{ 1.0f,2.0f },
		{ 0.0f,2.0f },//down
		{ -1.0f,2.0f },
		{ -1.0f,1.0f },//down_left
		{ -2.0f,1.0f },
		{ -2.0f,0.0f },//left
		{ -2.0f,-1.0f },
		{ -1.0f,-1.0f },//up_left
		{ -1.0f,-2.0f },
	};
};