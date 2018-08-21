#include "Player.h"

Player::Player(Car & car)
	:
	car(std::move(car))
{
}

void Player::update(Keyboard & kbd)
{
	if (kbd.KeyIsPressed(VK_UP))
	{
		car.speedup();
	}
	else if (kbd.KeyIsPressed(VK_DOWN))
	{
		car.speedup(false);
	}
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		car.turnLeft();
		
	}
	else if (kbd.KeyIsPressed(VK_RIGHT))
	{
		car.turnRight();
	}
	
	if (kbd.KeyIsPressed(VK_RETURN))
	{
		Debug::writeMessage(car.getDebugInfo());
	}

	if (kbd.KeyIsPressed('R'))
	{
		car.reset();
	}
	if (kbd.KeyIsPressed(VK_CONTROL))
	{
		car.shoot();
	}
	car.update();
}

void Player::draw(Graphics & gfx)
{
	car.draw(gfx);
}

const RectF& Player::getRect() const
{
	return car.getRect();
}
