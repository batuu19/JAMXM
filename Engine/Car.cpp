#include "Car.h"

Car::Car(VecF2 pos, int startDirection)
	:
	pos(pos),
	dir(startDirection)
{
}
Car::Car(VecI2 pos, int startDirection)
	:
	pos((float)pos.x,(float)pos.y),
	dir(startDirection)
{
}

void Car::turnLeft(float dt)
{
	if (leftTurnTime >= turnRate)
	{
		dir = (dir - turnValue + DIRECTIONS_COUNT) % DIRECTIONS_COUNT;
		leftTurnTime = 0.f;
		if (turnSoundTime >= turnSoundRate)
		{
			sndFriction.Play();
			turnSoundTime = 0.f;
		}
		
	}
	leftTurnTime += dt;
	turnSoundTime += dt;

	vel = vectorsNormalized[dir] * (vel * vectorsNormalized[dir]);
}

void Car::turnRight(float dt)
{
	if (rightTurnTime >= turnRate)
	{
		dir = (dir + turnValue) % DIRECTIONS_COUNT;
		rightTurnTime = 0.f;
		if (turnSoundTime >= turnSoundRate)
		{
			sndFriction.Play();
			turnSoundTime = 0.f;
		}
	}
	rightTurnTime += dt;
	turnSoundTime += dt;

	vel = vectorsNormalized[dir] * (vel * vectorsNormalized[dir]);
}

void Car::update(float dt, TurnDirection nextTurn)
{	
	for (auto &r : rocketsFired)
	{
		r.update(dt);
	}
	if (nextTurn == TurnDirection::Right)
	{
		turnRight(dt);
	}
	else if (nextTurn == TurnDirection::Left)
	{
		turnLeft(dt);
	}
	pos += vel;
}

void Car::speedup(bool faster)
{
	float value = vel * vectorsNormalized[dir];
	if(value < maxVel  && faster)
		vel += vectorsNormalized[dir] * speed;
	else if (value > -maxVel  && !faster)
		vel += vectorsNormalized[dir] * -speed;
}

void Car::draw(Graphics & gfx) const
{
	drawCar(gfx);
	for (auto r : rocketsFired)
	{
		r.draw(gfx);
	}

}

void Car::reset()
{
	pos = { 0.f,0.f };
	dir = RIGHT;
	vel = { 0.f,0.f };

	rocketsFired.clear();
}

void Car::shoot(float dt)
{
	if (lastShot >= shootRate)
	{
		rocketsFired.emplace_back(pos,vectorsNormalized[dir] * rocketVel,rocketSprites[dir]);
		lastShot = 0.f;
		sndRocketShot.Play();
	}
	
	lastShot += dt;
}

std::vector<Rocket>& Car::getRocketContainer()
{
	return rocketsFired;
}

const RectF& Car::getRect() const
{
	return RectF(pos,width,height);
}

std::string Car::getDebugInfo() const
{
	std::stringstream ss;

	ss  << "x=" << pos.x << " y=" << pos.y 
	    << " velX=" << vel.x << " velY=" << vel.y 
		<< " maxVel=" << maxVel;

	return ss.str();
}

void Car::drawCar(Graphics & gfx) const
{
	gfx.drawSprite((VecI2)pos, sprites[dir]);
}