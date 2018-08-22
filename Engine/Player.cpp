#include "Player.h"

Player::Player(Car& car)
	:
	car(car)
{
}

void Player::update(float dt)
{
	car.update(dt,nextTurn);
	nextTurn = Car::TurnDirection::None;
	if (shooting)
	{
		car.shoot(dt);
		shooting = false;
	}
	if (speedup < Car::Speedup::None)
	{
		car.speedup(dt, speedup);
		speedup = Car::Speedup::None;
	}
}

void Player::draw(Graphics & gfx) const
{
	car.draw(gfx);
}

const RectF& Player::getRect() const
{
	return car.getRect();
}

//TODO: better
void Player::handleInput(Keyboard & kbd, Mouse & mouse)
{
	if (kbd.KeyIsPressed(VK_UP))
	{
		speedup = Car::Speedup::Faster;
	}
	else if (kbd.KeyIsPressed(VK_DOWN))
	{
		speedup = Car::Speedup::Slower;
	}
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		nextTurn = Car::TurnDirection::Left;

	}
	else if (kbd.KeyIsPressed(VK_RIGHT))
	{
		nextTurn = Car::TurnDirection::Right;
	}

	if (kbd.KeyIsPressed(VK_RETURN))
	{
		//Debug::writeMessage(car.getDebugInfo());
	}

	if (kbd.KeyIsPressed('R'))
	{
		car.reset();
	}
	if (kbd.KeyIsPressed(VK_CONTROL))
	{
		shooting = true;
	}
}

const Car & Player::getCarConst() const
{
	return car;
}
