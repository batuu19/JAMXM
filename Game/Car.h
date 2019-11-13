#pragma once

#include <assert.h>
#include <sstream>
#include "SpriteContainer.h"
#include "Rocket.h"
#include "SoundEffect.h"
#include "Keyboard.h"
#include "Mouse.h"

#include "Entity.h"
class Car : public Entity
{

public:
	Car(VecF2 pos, int startDirection, std::vector<Rocket*>& rockets,std::vector<Animation>&);

	//make functors?
	enum class Speedup {
		Faster,
		Slower,
		None
	};
	enum class TurnDirection {
		Right,
		Left,
		None
	};
	void update(float dt) override;
	void speedup(float dt, Speedup speedupFlag = Speedup::Faster);
	void draw(Graphics&, const VecF2& cameraPos) const override;
	void reset() override;
	void stop();
	void bounceBack(bool forceBounce = false);
	void turnLeft();
	void turnRight();

	const VecF2& getVelConst() const;
	const VecF2& getPosConst() const;

	std::string getDebugInfo() const;

	void changeWeapon();
	Rocket* shoot(float dt);

	int getDir() const;

private:
	//make it dependent on velocity
	float turnRate = 0.1f;
	float leftTurnTime = turnRate;
	float rightTurnTime = turnRate;
	int turnValue = 1;//how many directions at once
	Sound sndFriction = Sound( L"sound\\game\\friction.wav" );


	Sound sndWeaponChange = Sound(L"sound\\game\\reload.wav");

	TurnDirection nextTurn = TurnDirection::None;

	//rocket
	int rocketCount = 2;
	enum class RocketType
	{
		SmallRocket,
		BigRocket
	};
	RocketType rocketType = RocketType::SmallRocket;
	std::vector<Rocket*>& rocketsFired;
	float lastShot = 0.f;
	Sound sndRocketShot = Sound( L"sound\\game\\rocketshot.wav" );
	bool shooting = false;

	std::vector<Animation>& animations;
};
