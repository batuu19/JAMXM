#include "CarController.h"

CarController::CarController(std::shared_ptr<Car> car, const Map& map,
	std::shared_ptr<std::vector<std::shared_ptr<Rocket>>> rocketsFired,
	std::shared_ptr<std::vector<std::shared_ptr<Animation>>> animations)
	:
	Entity(VecF2(map.getCarStartPos()), map.getCarStartDirection(),
		SpriteContainer({ car->spriteSrc }, 5, 1),
		{ 0.f,0.f }, car->maxHP, car->speed, car->maxVel,
		1.f, true),
	car(car),
	carStartPos(map.getCarStartPos()),
	carStartDirection(map.getCarStartDirection()),
	turnRate(car->turnRate),
	turnValue(car->turnValue),
	rocketsFired(rocketsFired),
	animations(animations)

{
}

void CarController::update(float dt)//make it shorter and divide in parts?
{
	//TODO: one turn time
	rightTurnTime += dt;
	leftTurnTime += dt;
	lastShot += dt;
	for (auto r : *rocketsFired)
	{
		r->update(dt);
	}
	if (speedupFlag < Speedup::None)
		speedup(dt);
	if (shootFlag)
		shoot(dt);
	if (turnFlag < TurnDirection::None)
		turn(dt);
	

	Entity::update(dt);
}

void CarController::draw(Graphics& gfx, const VecF2& cameraPos) const
{
	Entity::draw(gfx, cameraPos);
	//make it not responsible for drawing rockets
	for (auto r : *rocketsFired)
	{
		r->draw(gfx, cameraPos);
	}
}

void CarController::handleInput(Keyboard::Event e)
{
	if (e.IsPress())
	{
		switch (e.GetCode())
		{
			//controling car
		case INPUT_ACC:
			speedupFlag = Speedup::Faster;
			break;
		case INPUT_BREAKE:
			speedupFlag = Speedup::Slower;
			break;
		case INPUT_TURN_LEFT:
			turnFlag = TurnDirection::Left;
			break;
		case INPUT_TURN_RIGHT:
			turnFlag = TurnDirection::Right;
			break;
		case INPUT_SHOOT:
			shootFlag = true;
			break;
		case INPUT_CHANGE_WEAPON:
			changeWeapon();
			break;
		default:
			break;
		}
	}
	if (e.IsRelease())
	{
		switch (e.GetCode())
		{
		case INPUT_ACC:
			speedupFlag = Speedup::None;
			break;
		case INPUT_BREAKE:
			speedupFlag = Speedup::None;
			break;
		case INPUT_TURN_LEFT:
			turnFlag = TurnDirection::None;
			break;
		case INPUT_TURN_RIGHT:
			turnFlag = TurnDirection::None;
			break;
		case INPUT_SHOOT:
			shootFlag = false;
			break;
		default:
			break;
		}
	}
}

void CarController::reset()
{
	score = 0;
	pos = VecF2(carStartPos);
	spriteState = carStartDirection;
	vel = VecF2::zero();

	rocketsFired->clear();
	Entity::reset();
}

void CarController::stop()
{
	vel = VecF2::zero();
}

void CarController::bounceBack(bool forceBounce)
{
	vel = -vel;
	if (forceBounce)vel += vectorsNormalized[getOpposite(spriteState)] * 200.f;
}

void CarController::scorePoints(int amount)
{
	score += amount;
}

void CarController::changeWeapon()
{
	rocketType = static_cast<Rocket::Type>((static_cast<int>(rocketType) + 1) % rocketCount);//next weapon
	//sndWeaponChange.Play();//TODO
}

void CarController::speedup(float dt)
{
	float value = vel * vectorsNormalized[spriteState];
	if (value < maxVel && (speedupFlag == Speedup::Faster))
		vel += vectorsNormalized[spriteState] * speed * dt;
	else if (value > -maxVel && (speedupFlag == Speedup::Slower))
		vel += vectorsNormalized[spriteState] * -speed * dt;
}

void CarController::shoot(float dt)
{
	std::shared_ptr<Rocket> nextRocket;
	switch (rocketType)
	{
	case Rocket::Type::SmallRocket:
		if (lastShot > SmallRocket::shootRate)
		{
			sndRocketShot.Play();
			nextRocket = std::make_shared<SmallRocket>(pos, spriteState);
			lastShot = 0.f;
		}
		else return;
		break;
	case Rocket::Type::BigRocket:
		if (lastShot > BigRocket::shootRate)
		{
			sndRocketShot.Play();
			nextRocket = std::make_shared<BigRocket>(pos, spriteState, animations);
			lastShot = 0.f;
		}
		else return;
		break;
	}

	rocketsFired->push_back(nextRocket);
}

void CarController::turn(float dt)
{
	if (turnFlag == TurnDirection::Right)
	{
		if (rightTurnTime >= turnRate)
		{
			spriteState = (spriteState + turnValue) % DIRECTIONS_COUNT;
			rightTurnTime = 0.f;
			vel = vectorsNormalized[spriteState] * (vel * vectorsNormalized[spriteState]);
		}
		//turnFlag = TurnDirection::None;
	}
	else if (turnFlag == TurnDirection::Left)
	{
		if (leftTurnTime >= turnRate)
		{
			spriteState = (spriteState - turnValue + DIRECTIONS_COUNT) % DIRECTIONS_COUNT;
			leftTurnTime = 0.f;

			vel = vectorsNormalized[spriteState] * (vel * vectorsNormalized[spriteState]);
		}
		//turnFlag = TurnDirection::None;
	}
}

const Car& CarController::getCarConst() const
{
	return *car;
}

int CarController::getDir() const
{
	return spriteState;
}