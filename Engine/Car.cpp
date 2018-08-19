#include "Car.h"

Car::Car(Config& config)
	:
	pos(config.getCarStartXPos(), config.getCarStartYPos()),
	speed(config.getCarSpeed()),
	maxVel(config.getCarMaxVelocity()),
	dir(config.getCarStartDir()),
	turnRate(config.getCarTurnRate()),
	config(config),
	sprites(config.getCarImageFileName(),5,1,70,70)
{
	
	for (auto& v : directionVec)
	{
		v.normalize();
	}
	vel = { 0.0f,0.0f };
}

void Car::turnLeft()
{
	const float dt = ft.mark();
	if (leftTurn >= turnRate)
	{
		dir = (dir - turnValue + DIRECTIONS_COUNT) % DIRECTIONS_COUNT;
		leftTurn = 0.0f;
	}
	leftTurn += dt;

	vel = directionVec[dir] * (vel * directionVec[dir]);
}

void Car::turnRight()
{
	const float dt = ft.mark();

	if (rightTurn >= turnRate)
	{
		dir = (dir + turnValue) % DIRECTIONS_COUNT;
		rightTurn = 0.0f;
	}
	rightTurn += dt;

	vel = directionVec[dir] * (vel * directionVec[dir]);
}

void Car::update()
{	
	pos += vel;
}

void Car::speedup(bool faster)
{
	float speedFactor = faster ? speed : -speed;
	const float actualVelSq = vel.getLengthSq();
	//TODO: that's bad, can't stop when max or 0 vel
	if(actualVelSq < maxVel * maxVel && actualVelSq >= 0)
		vel +=  directionVec[dir] * speedFactor;
}

void Car::draw(Graphics & gfx) const
{
	drawCar(gfx);
}

void Car::reset()
{
	pos.x = (float)config.getCarStartXPos();
	pos.y = (float)config.getCarStartYPos();
	dir = config.getCarStartDir();
	vel = { 0.0f,0.0f };
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
	gfx.drawSprite((Vei2)pos, sprites[dir]);
}