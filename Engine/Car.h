#pragma once

#include <assert.h>
#include <sstream>
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
	enum class WeaponType
	{
		SMALL_ROCKET,
		BIG_ROCKET,
		WEAPON_COUNT
	};
	void changeWeapon();
	void changeWeapon(WeaponType weapon);
	Sound sndWeaponChange = Sound(L"sound//game//reload.wav");
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
	WeaponType weaponType = WeaponType::SMALL_ROCKET;
	std::vector<SpriteContainer> rocketSprites;

	std::vector<float> rocketVel = { 700.f,400.f };
	std::vector<Rocket>& rocketsFired;
	std::vector<float> shootRate = { 0.23f,0.45f };
	float lastShot = shootRate[0];
	Sound sndRocketShot = Sound( L"sound\\game\\rocketshot.wav" );
};
