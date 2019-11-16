#pragma once

#include "Entity.h"
#include "Car.h"
#include "Map.h"
#include "Rocket.h"
#include <memory>

static constexpr unsigned char INPUT_ACC = VK_UP;
static constexpr unsigned char INPUT_BREAKE = VK_DOWN;
static constexpr unsigned char INPUT_TURN_LEFT = VK_LEFT;
static constexpr unsigned char INPUT_TURN_RIGHT = VK_RIGHT;
static constexpr unsigned char INPUT_RESET = 'R';
static constexpr unsigned char INPUT_SHOOT = VK_CONTROL;
static constexpr unsigned char INPUT_CHANGE_WEAPON = 'Q';
//add next and prev weapon

class CarController :
	public Entity,
	public PlayableEntity
{
public:
	CarController(std::shared_ptr<Car> car, const Map& map,
		std::shared_ptr<std::vector<std::shared_ptr<Rocket>>> rocketsFired,
		std::shared_ptr<std::vector<std::shared_ptr<Animation>>> animations
		);
	void update(float dt) override;
	void draw(Graphics&, const VecF2& cameraPos) const override;
	void handleInput(Keyboard::Event) override;
	void reset() override;
	void stop();
	void bounceBack(bool forceBounce = false);
	void scorePoints(int amount = 1);

	void changeWeapon();

	//from update
	void speedup(float dt);
	void shoot(float dt);
	void turn(float dt);

	const Car& getCarConst() const;
	int getDir() const;
public:
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
private:
	std::shared_ptr<Car> car;
	VecI2 carStartPos;
	int carStartDirection;
	float turnRate;
	float leftTurnTime = turnRate;
	float rightTurnTime = turnRate;
	int turnValue;//how many directions at once
	Speedup speedupFlag = Speedup::None;
	bool shootFlag = false;
	TurnDirection turnFlag = TurnDirection::None;
	int score = 0;

	//rocket
	int rocketCount = static_cast<int>(Rocket::Type::None);
	Rocket::Type rocketType = Rocket::Type::SmallRocket;
	std::shared_ptr<std::vector<std::shared_ptr<Rocket>>> rocketsFired;
	float lastShot = 0.f;
	Sound sndRocketShot;

	std::shared_ptr<std::vector<std::shared_ptr<Animation>>> animations;

};
