#include "Player.h"
#include "UI.h"

Player::Player(std::shared_ptr<Car> car)
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

void Player::draw(Graphics& gfx, const VecF2& cameraPos) const
{
	car->draw(gfx, cameraPos);
}

void Player::reset()
{
	score = 0;
	car->reset();
}

void Player::scorePoints(int amount)
{
	score += amount;
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

const Car& Player::getCarConst() const
{
	return *car;
}

