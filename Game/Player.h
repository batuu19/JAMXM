#pragma once
#include "Car.h"
#include <memory>

class Player 
{
public:
	Player(std::shared_ptr<Car>);
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;
	const Car& getCarConst() const;

private:
	std::shared_ptr<Car> car;//make unique_ptr?
	int money = 0;


};
