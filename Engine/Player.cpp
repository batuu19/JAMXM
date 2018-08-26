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

void Player::draw(Graphics & gfx, VecF2 cameraPos) const
{
	car.draw(gfx,cameraPos);
}


//TODO: better
void Player::handleInput(Keyboard & kbd, Mouse & mouse)
{
	//for one key at once
	while (!kbd.KeyIsEmpty())
	{
		const Keyboard::Event e = kbd.ReadKey();

		if (e.IsPress())
		{
			if (e.GetCode() == 'Q')
				car.changeWeapon();
		}
	}
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

