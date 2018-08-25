#include "Car.h"

Car::Car(VecF2 pos, int startDirection, std::vector<Rocket>& rockets)
	:
	pos(pos),
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
	draw(gfx, { 0.f,0.f });
}

void Car::draw(Graphics & gfx, VecF2 cameraPos) const
{
	drawCar(gfx,cameraPos);
	for (auto& r : rocketsFired)
	{
		r.draw(gfx,cameraPos);
	}
}

void Car::reset()
{
	pos = { 400.f,300.f };
	dir = RIGHT;
	vel = { 0.f,0.f };

	rocketsFired.clear();
}

void Car::stop()
{
	vel = getZeroVec<float>();
}

void Car::bounceBack()
{
	vel = -vel;
}

const VecF2 & Car::getVelConst() const
{
	return vel;
}

const VecF2 & Car::getPosConst() const
{
	return pos;
}

void Car::shoot(float dt)
{
	if (lastShot >= shootRate)
	{
		Rocket toPush(pos, vectorsNormalized[dir] * rocketVel, rocketSprites[dir] );
		rocketsFired.push_back(std::move(toPush));
		lastShot = 0.f;
		sndRocketShot.Play();
	}
	
}


RectF Car::getHitbox() const
{
	return RectF(pos,width,height);
}

int Car::getDir() const
{
	return dir;
}

std::string Car::getDebugInfo() const
{
	std::stringstream ss;

	ss  << "x=" << pos.x << " y=" << pos.y 
	    << " velX=" << vel.x << " velY=" << vel.y 
		<< " maxVel=" << maxVel;

	return ss.str();
}

void Car::drawCar(Graphics & gfx,VecF2 cameraPos) const
{
	gfx.drawSprite(pos + cameraPos, sprites[dir]);
}