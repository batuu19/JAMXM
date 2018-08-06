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

		//todo slower
		car.turnLeft();
	}
	else if (kbd.KeyIsPressed(VK_RIGHT))
	{
		//todo slower
		car.turnRight();
	}

	car.update();
}

void Player::draw(Graphics & gfx)
{
	car.draw(gfx);
}
