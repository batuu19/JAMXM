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
		}
		if (speedup < Car::Speedup::None)
		{
			car->speedup(dt, speedup);
		}
		switch (turning)
		{
		case Car::TurnDirection::Right:
			car->turnRight();
			break;
		case Car::TurnDirection::Left:
			car->turnLeft();
			break;
		case Car::TurnDirection::None:
			break;
		}
	}
}

void Player::draw(Graphics & gfx, const VecF2& cameraPos) const
{
	car->draw(gfx,cameraPos);
}

void Player::reset()
{
	score = 0;
	car->reset();
}

void Player::scorePoint()
{
	score++;
}

void Player::handleInput(Keyboard::Event e)
{
	if (e.IsPress())
	{
		switch (e.GetCode())
		{
		case 'Q':
			car->changeWeapon();
			break;
		case VK_CONTROL:
			shooting = true;
			break;
		//controling car
		case VK_UP:
			speedup = Car::Speedup::Faster;
			break;
		case VK_DOWN:
			speedup = Car::Speedup::Slower;
			break;
		case VK_LEFT:
			turning = Car::TurnDirection::Left;
			break;
		case VK_RIGHT:
			turning = Car::TurnDirection::Right;
			break;
		default:
			break;
		}
	}
	if (e.IsRelease())
	{
		switch (e.GetCode())
		{
		case VK_CONTROL:
			shooting = false;
			break;
		case VK_UP:
			speedup = Car::Speedup::None;
			break;
		case VK_DOWN:
			speedup = Car::Speedup::None;
			break;
		case VK_LEFT:
			turning = Car::TurnDirection::None;
			break;
		case VK_RIGHT:
			turning = Car::TurnDirection::None;
			break;
		default:
			break;
		}
	}
}

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
	gfx.drawSprite(VecI2{ 100,50 }, Font::getChar('0' + player.score));
}
