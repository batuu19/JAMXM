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
#include "Keyboard.h"
#include "Mouse.h"

//TODO: add collision using RectI
class Car
{

public:
	Car(VecF2 pos, int startDirection);
	Car(VecI2 pos, int startDirection);
	//make functors?
	enum class TurnDirection {
		Right,
		Left,
		None
	};
	void update(float dt,TurnDirection nextTurn = TurnDirection::None);
	void speedup(bool faster = true);
	void draw(Graphics&) const;
	void reset();

	std::string getDebugInfo() const;

	//rocket
	void shoot(float dt);
	std::vector<Rocket>& getRocketContainer();

	//collision
	const RectF& getRect() const;

private:
	int dir;
	VecF2 pos;
	VecF2 vel = { 0.f,0.f };
	int width = 70;
	int height = 70;
	float speed = 0.3f;//speedup rate
	float maxVel = 6.f;

	SpriteContainer sprites = SpriteContainer({"sprites\\car.bmp"},5,1,width,height);

	//make it dependent on velocity
	void turnLeft(float dt);
	void turnRight(float dt);
	float turnRate = 0.1f;
	float leftTurnTime = 0.f;
	float rightTurnTime = 0.f;
	int turnValue = 1;//how many directions at once
	Sound sndFriction = Sound( L"sound\\game\\friction.wav" );
	float turnSoundRate = turnRate * 3.1f;
	float turnSoundTime = 0.f;

	void drawCar(Graphics &) const;

	//rocket
	int rocketWidth = 35;
	int rocketHeight = 35;
	SpriteContainer rocketSprites = SpriteContainer({ "sprites//rocket1.bmp" }, 5, 1, rocketWidth, rocketHeight);
	float rocketVel = 12;
	std::vector<Rocket> rocketsFired;
	float shootRate = 0.1f;
	float lastShot = 0.f;
	Sound sndRocketShot = Sound( L"sound\\game\\rocketshot.wav" );

	//collision
};
