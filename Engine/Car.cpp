#include "Car.h"

Car::Car(const Config& config)
	:
	pos(config.getCarStartXPos(), config.getCarStartYPos()),
	speed(config.getCarSpeed()),
	maxVel(config.getCarMaxVelocity()),
	dir(config.getCarStartDir()),
	turnRate(config.getCarTurnRate()),
	config(config),
	sprites(config.getCarImageFileName(),5,1,70,70)
{
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

	vel = vectorsNormalized[dir] * (vel * vectorsNormalized[dir]);
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
	float speedFactor = faster ? speed : -speed;
	const float actualVelSq = vel.getLengthSq();
	//TODO: that's bad, can't stop when max or 0 vel
	if(actualVelSq < maxVel * maxVel && actualVelSq >= 0)
		vel += vectorsNormalized[dir] * speedFactor;
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
	pos.x = (float)config.getCarStartXPos();
	pos.y = (float)config.getCarStartYPos();
	dir = config.getCarStartDir();
	vel = { 0.0f,0.0f };

	rocketsFired.clear();
}

void Car::shoot()
{
	rocketsFired.emplace_back( config,pos,dir );
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