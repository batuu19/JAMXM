#include "Car.h"

Car::Car(VecF2 pos, int startDirection, std::vector<Rocket>& rockets)
	:
	pos(pos),
	dir(startDirection),
	rocketsFired(rockets)
{
}
Car::Car(VecI2 pos, int startDirection, std::vector<Rocket>& rockets)
	:
	pos((float)pos.x,(float)pos.y),
	dir(startDirection),
	rocketsFired(rockets)
{
}

void Car::update(float dt, TurnDirection nextTurn)
{
	//TODO: one turn time
	rightTurnTime += dt;
	leftTurnTime += dt;
	turnSoundTime += dt;
	lastShot += dt;
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
	pos += vel * dt;
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

	vel = vectorsNormalized[dir] * (vel * vectorsNormalized[dir]);
}

void Car::speedup(float dt, Speedup speedupFlag)
{
	float value = vel * vectorsNormalized[dir];
	if(value < maxVel  && (speedupFlag == Speedup::Faster))
		vel += vectorsNormalized[dir] * speed * dt;
	else if (value > -maxVel  && (speedupFlag == Speedup::Slower))
		vel += vectorsNormalized[dir] * -speed * dt;
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
	
}

const RectF& Car::getRect() const
{
	return RectF(pos,width,height);
}

RectF Car::getHitbox() const
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