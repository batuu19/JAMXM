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
	Car(VecF2 pos, int startDirection, std::vector<Rocket>& rockets);
	Car(const Car&) = delete;
	//make functors?
	enum class TurnDirection {
		Right,
		Left,
		None
	};
	enum class Speedup {
		Faster,
		Slower,
		None
	};
	void update(float dt,TurnDirection nextTurn = TurnDirection::None);
	void speedup(float dt, Speedup speedupFlag = Speedup::Faster);
	void draw(Graphics&) const;
	void draw(Graphics&, VecF2 cameraPos) const;
	void reset();
	void stop();
	void bounceBack();

	const VecF2& getVelConst() const;
	const VecF2& getPosConst() const;

	std::string getDebugInfo() const;

	//rocket
	void shoot(float dt);

	//TODO: fix - more accurate hitbox
	RectF getHitbox() const;

	int getDir() const;

private:
	int dir;
	VecF2 pos;
	VecF2 vel = { 0.f,0.f };
	int width = 70;
	int height = 70;
	float speed = 600.f;//speedup rate
	float maxVel = 300.f;

	SpriteContainer sprites = SpriteContainer({"sprites\\cars\\car_black_350x70.bmp"},5,1,width,height);

	//make it dependent on velocity
	void turnLeft(float dt);
	void turnRight(float dt);
	float turnRate = 0.1f;
	float leftTurnTime = turnRate;
	float rightTurnTime = turnRate;
	int turnValue = 1;//how many directions at once
	Sound sndFriction = Sound( L"sound\\game\\friction.wav" );
	float turnSoundRate = turnRate * 3.1f;
	float turnSoundTime = 0.f;

	void drawCar(Graphics &,VecF2 cameraPos) const;

	//rocket
	int rocketWidth = 35;
	int rocketHeight = 35;
	SpriteContainer rocketSprites = SpriteContainer({ "sprites//small_rocket_175x35.bmp" }, 5, 1, rocketWidth, rocketHeight);
	float rocketVel = 900.f;
	std::vector<Rocket>& rocketsFired;
	float shootRate = 0.3f;
	float lastShot = shootRate;
	Sound sndRocketShot = Sound( L"sound\\game\\rocketshot.wav" );
};
