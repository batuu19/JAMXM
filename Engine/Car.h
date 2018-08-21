#pragma once

#include "Graphics.h"
#include "Directions.h"
#include "FrameTimer.h"
#include <math.h>
#include <algorithm>
#include <assert.h>
#include <sstream>
#include "Surface.h"
#include <vector>
#include "BMath.h"
#include "SpriteContainer.h"
#include "Rocket.h"
#include "SoundEffect.h"

//TODO: add collision using RectI
class Car
{

public:
	//TODO: without config
	Car(VecF2 pos, float startVel, float speed, float maxVel, int startDirection, float turnRate,
		float rocketVel, std::string rocketSpriteFilename, int rocketWidth, int rocketHeight,
		std::string spriteFilename, int spriteWidth, int spriteHeight, int spritesRows = 5, int spritesLines = 1);

	//make functors?
	void turnLeft();
	void turnRight();
	void update();
	void speedup(bool faster = true);
	void draw(Graphics&) const;
	void reset();

	std::string getDebugInfo() const;

	//rocket
	void shoot();

	//collision
	RectF getRect() const;
private:
	int dir;
	VecF2 pos;
	VecF2 vel;
	int width;
	int height;
	float speed;//speedup rate
	float maxVel;

	SpriteContainer sprites;

	//turning
	FrameTimer turnTimer;
	//make it dependent on velocity
	float turnRate;
	float leftTurn = 0.f;
	float rightTurn = 0.f;
	int turnValue = 1;//how many directions at once
	Sound sndFriction = Sound( L"sound\\game\\friction.wav" );
	FrameTimer turnSoundTimer;
	float turnSoundRate;
	float turnSound = 0.f;

	void drawCar(Graphics &) const;

	//rocket
	SpriteContainer rocketSprites;
	int rocketWidth;
	int rocketHeight;
	float rocketVel;
	std::vector<Rocket> rocketsFired;
	FrameTimer shootTimer;
	float shootRate = 0.7f;
	float lastShot = 0.f;
	Sound sndRocketShot = Sound( L"sound\\game\\rocketshot.wav" );

	//collision
};