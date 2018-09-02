#include "Car.h"

Car::Car(VecF2 pos, int startDirection, std::vector<Rocket*>& rockets)
	:
	Entity(pos, startDirection, SpriteContainer({ "Sprites\\cars\\car_black_350x70.bmp" }, 5, 1, 70, 70), { 0.f,0.f }, 100.f, 600.f, 300.f),
	rocketsFired(rockets)
{
}

void Car::update(float dt)
{
	//TODO: one turn time
	rightTurnTime += dt;
	leftTurnTime += dt;
	turnSoundTime += dt;
	lastShot += dt;
	for (auto r : rocketsFired)
	{
		r->update(dt);
	}
	if (nextTurn == TurnDirection::Right)
	{
		if (rightTurnTime >= turnRate)
		{
			spriteState = (spriteState + turnValue) % DIRECTIONS_COUNT;
			rightTurnTime = 0.f;
			if (turnSoundTime >= turnSoundRate)
			{
				sndFriction.Play();
				turnSoundTime = 0.f;
			}
			vel = vectorsNormalized[spriteState] * (vel * vectorsNormalized[spriteState]);
		}
		nextTurn = TurnDirection::None;
	}
	else if (nextTurn == TurnDirection::Left)
	{
		if (leftTurnTime >= turnRate)
		{
			spriteState = (spriteState - turnValue + DIRECTIONS_COUNT) % DIRECTIONS_COUNT;
			leftTurnTime = 0.f;
			if (turnSoundTime >= turnSoundRate)
			{
				sndFriction.Play();
				turnSoundTime = 0.f;
			}

			vel = vectorsNormalized[spriteState] * (vel * vectorsNormalized[spriteState]);
		}
		nextTurn = TurnDirection::None;
	}

	Entity::update(dt);
}

void Car::turnLeft()
{
	nextTurn = TurnDirection::Left;
}

void Car::turnRight()
{
	nextTurn = TurnDirection::Right;
}

void Car::speedup(float dt, Speedup speedupFlag)
{
	float value = vel * vectorsNormalized[spriteState];
	if(value < maxVel  && (speedupFlag == Speedup::Faster))
		vel += vectorsNormalized[spriteState] * speed * dt;
	else if (value > -maxVel  && (speedupFlag == Speedup::Slower))
		vel += vectorsNormalized[spriteState] * -speed * dt;
}


void Car::draw(Graphics & gfx, const VecF2& cameraPos) const
{
	Entity::draw(gfx, cameraPos);
	for (auto r : rocketsFired)
	{
		r->draw(gfx,cameraPos);
	}
}

void Car::reset()
{
	pos = { 400.f,300.f };
	spriteState = RIGHT;
	vel = { 0.f,0.f };

	rocketsFired.clear();
}

void Car::stop()
{
	vel = getZeroVec<float>();
}

void Car::bounceBack(bool forceBounce)
{
	vel = -vel;
	if (forceBounce)vel += vectorsNormalized[getOpposite(spriteState)] *  200.f;
}

const VecF2 & Car::getVelConst() const
{
	return vel;
}

const VecF2 & Car::getPosConst() const
{
	return pos;
}

void Car::changeWeapon()
{
	rocketType = static_cast<RocketType>((static_cast<int>(rocketType) + 1) % rocketCount);//next weapon
	sndWeaponChange.Play();
}

void Car::shoot(float dt)
{
	Rocket* nextRocket = nullptr;
	switch (rocketType)
	{
	case Car::RocketType::SmallRocket:
		if (lastShot > SmallRocket::shootRate)
		{
			sndRocketShot.Play();
			nextRocket = new SmallRocket(pos, spriteState);
			lastShot = 0.f;
		}
		else return;
		break;
	case Car::RocketType::BigRocket:
		if (lastShot > BigRocket::shootRate)
		{
			sndRocketShot.Play();
			nextRocket = new BigRocket(pos, spriteState);
			lastShot = 0.f;
		}
		else return;
		break;
	}

	rocketsFired.push_back(nextRocket);
}

int Car::getDir() const
{
	return spriteState;
}

std::string Car::getDebugInfo() const
{
	std::stringstream ss;

	ss  << "x=" << pos.x << " y=" << pos.y 
	    << " velX=" << vel.x << " velY=" << vel.y 
		<< " maxVel=" << maxVel;

	return ss.str();
}
