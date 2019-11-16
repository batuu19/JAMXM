#include "Car.h"

Car::Car(VecF2 pos, int startDirection, 
	std::shared_ptr<std::vector<std::shared_ptr<Rocket>>> rockets,
	std::shared_ptr<std::vector<std::shared_ptr<Animation>>> animations)
	:
	Entity(pos, startDirection, SpriteContainer({ "Sprites\\cars\\car_black.bmp" }, 5, 1),
		{ 0.f,0.f }, 300.f, 600.f, 300.f,
		1.f, true
	),
	rocketsFired(rockets),
	animations(animations)
{
}

void Car::update(float dt)
{
	//TODO: one turn time
	rightTurnTime += dt;
	leftTurnTime += dt;
	lastShot += dt;
	for (auto r : *rocketsFired)
	{
		r->update(dt);
	}
	if (nextTurn == TurnDirection::Right)
	{
		if (rightTurnTime >= turnRate)
		{
			spriteState = (spriteState + turnValue) % DIRECTIONS_COUNT;
			rightTurnTime = 0.f;
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
	if (value < maxVel && (speedupFlag == Speedup::Faster))
		vel += vectorsNormalized[spriteState] * speed * dt;
	else if (value > -maxVel && (speedupFlag == Speedup::Slower))
		vel += vectorsNormalized[spriteState] * -speed * dt;
}


void Car::draw(Graphics& gfx, const VecF2& cameraPos) const
{
	Entity::draw(gfx, cameraPos);
	for (auto r : *rocketsFired)
	{
		r->draw(gfx, cameraPos);
	}

	//gfx.drawRect(hitbox.rect.getDisplacedBy(hitbox.pos - cameraPos), Colors::Green);
}

void Car::reset()
{
	pos = { 400.f,300.f };
	spriteState = RIGHT;
	vel = { 0.f,0.f };

	rocketsFired->clear();
	Entity::reset();
}

void Car::stop()
{
	vel = Vec2<float>::zero();
}

void Car::bounceBack(bool forceBounce)
{
	vel = -vel;
	if (forceBounce)vel += vectorsNormalized[getOpposite(spriteState)] * 200.f;
}

const VecF2& Car::getVelConst() const
{
	return vel;
}

const VecF2& Car::getPosConst() const
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
	//Rocket* nextRocket = nullptr;
	std::shared_ptr<Rocket> nextRocket;
	switch (rocketType)
	{
	case Car::RocketType::SmallRocket:
		if (lastShot > SmallRocket::shootRate)
		{
			sndRocketShot.Play();
			nextRocket = std::make_shared<SmallRocket>(pos, spriteState);
			lastShot = 0.f;
		}
		else return;
		break;
	case Car::RocketType::BigRocket:
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

int Car::getDir() const
{
	return spriteState;
}

std::string Car::getDebugInfo() const
{
	std::stringstream ss;

	ss << "x=" << pos.x << " y=" << pos.y
		<< " velX=" << vel.x << " velY=" << vel.y
		<< " maxVel=" << maxVel;

	return ss.str();
}
