#include "Player.h"
#include "UI.h"

Player::Player(std::shared_ptr<Car> car)
	:
	car(car)
{
}

const Car& Player::getCarConst() const
{
	return *car;
}

