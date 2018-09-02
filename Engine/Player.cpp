#include "Player.h"

Player::Player(Car* car)
	:
	car(car)
{
}

Player::~Player()
{
}

void Player::update(float dt)
{
	if (car != NULL)
	{
		car->update(dt);
		if (shooting)
		{
			car->shoot(dt);
			shooting = false;
		}
		if (speedup < Car::Speedup::None)
		{
			car->speedup(dt, speedup);
			speedup = Car::Speedup::None;
		}
	}
}

void Player::draw(Graphics & gfx, const VecF2&  cameraPos) const
{
	assert(car != NULL);
	car->draw(gfx,cameraPos);
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
				car->changeWeapon();
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
		car->turnLeft();
	}
	else if (kbd.KeyIsPressed(VK_RIGHT))
	{
		car->turnRight();
	}

	if (kbd.KeyIsPressed(VK_RETURN))
	{
		//Debug::writeMessage(car.getDebugInfo());
	}

	if (kbd.KeyIsPressed('R'))
	{
		car->reset();
	}
	if (kbd.KeyIsPressed(VK_CONTROL))
	{
		shooting = true;
	}
}

//TODO: check if good
const Car & Player::getCarConst() const
{
	return *car;
}

UI::UI(Player & player)
	:
	player(player)
{
}

void UI::update(float dt)
{
	HPPercentage = player.car->HP / player.car->maxHP;
}

void UI::draw(Graphics & gfx, VecF2 cameraPos) const
{
	gfx.drawSprite(pos, background);
	gfx.drawRect(HPRect.getExpanded(0, (int)(HPRect.right*HPPercentage), 0, 0), HPcolor);
}
