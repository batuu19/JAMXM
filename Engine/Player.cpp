#include "Player.h"

Player::Player( Car & car)
	:
	car(car)
{
}

void Player::update(Keyboard & kbd)
{
	const float dt = ft.mark();

	if (kbd.KeyIsPressed(VK_UP))
	{
		car.speedup();
	}
	else if (kbd.KeyIsPressed(VK_DOWN))
	{
		car.speedup(false);
	}
	else if (kbd.KeyIsPressed(VK_LEFT))
	{
		car.turnLeft();
		
	}
	else if (kbd.KeyIsPressed(VK_RIGHT))
	{
		car.turnRight();
	}

	car.update();

	leftTurn += dt;
	rightTurn += dt;
}

void Player::draw(Graphics & gfx)
{
	car.draw(gfx);
}
