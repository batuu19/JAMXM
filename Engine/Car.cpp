#include "Car.h"

Car::Car(VecF2 pos, float startVel, float speed, float maxVel, int startDirection, float turnRate,
	float rocketVel,std::string rocketSpriteFilename, int rocketWidth, int rocketHeight,
	std::string spriteFilename, int spriteWidth, int spriteHeight, int spritesRows, int spritesLines)
	:
	pos(pos),
	vel(vectorsNormalized[dir] * startVel),
	dir(startDirection),
	speed(speed),
	maxVel(maxVel),
	turnRate(turnRate),
	turnSoundRate(turnRate * 3.1f),
	rocketWidth(rocketWidth),
	rocketHeight(rocketHeight),
	rocketSprites(rocketSpriteFilename,spritesRows,spritesLines,rocketWidth,rocketHeight),
	rocketVel(rocketVel),
	width(spriteWidth),
	height(spriteHeight),
	sprites(spriteFilename, spritesRows, spritesLines, width, height)
{
}

void Car::turnLeft()
{
	const float dt = turnTimer.mark();
	const float dts = turnSoundTimer.mark();
	if (leftTurn >= turnRate)
	{
		dir = (dir - turnValue + DIRECTIONS_COUNT) % DIRECTIONS_COUNT;
		leftTurn = 0.f;
		if (turnSound >= turnSoundRate)
		{
			sndFriction.Play();
			turnSound = 0.f;
		}
		
	}
	leftTurn += dt;
	turnSound += dts;

	vel = vectorsNormalized[dir] * (vel * vectorsNormalized[dir]);
}

void Car::turnRight()
{
	const float dt = turnTimer.mark();
	const float dts = turnSoundTimer.mark();

	if (rightTurn >= turnRate)
	{
		dir = (dir + turnValue) % DIRECTIONS_COUNT;
		rightTurn = 0.f;
		if (turnSound >= turnSoundRate)
		{
			sndFriction.Play();
			turnSound = 0.f;
		}
	}
	rightTurn += dt;
	turnSound += dts;

	vel = vectorsNormalized[dir] * (vel * vectorsNormalized[dir]);
}

void Car::update()
{	
	for (auto &r : rocketsFired)
	{
		r.update();
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

void Car::shoot()
{
	const float dt = shootTimer.mark();
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