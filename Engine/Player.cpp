#include "Player.h"

Player::Player( Car & car)
	:
	car(car)
	//here copying
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
	else if (kbd.KeyIsPressed(VK_LEFT))
	{
		car.turnLeft();
		
	}
	else if (kbd.KeyIsPressed(VK_RIGHT))
	{
		car.turnRight();
	}

	car.update();
}

void Player::draw(Graphics & gfx)
{
	car.draw(gfx);
}
