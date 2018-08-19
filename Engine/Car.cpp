#include "Car.h"

Car::Car(Config& config)
	:
	pos(config.getCarStartXPos(), config.getCarStartYPos()),
	speed(config.getCarSpeed()),
	maxVel(config.getCarMaxVelocity()),
	dir(config.getCarStartDir()),
	turnRate(config.getCarTurnRate()),
	vel(),//don't need that
	config(config)
{
	vel.normalize();
	//TODO: make class for this
	{
		RectI frames[] = {
			{ 0,70,0,70 },
			{ 70,140,0,70 },
			{ 140,210,0,70 },
			{ 210,280,0,70 },
			{ 280,350,0,70 }
		};

		Surface allCars(config.getCarImageFileName());

		sprites.emplace_back(allCars.getPart(frames[0]));//UP

		sprites.emplace_back(allCars.getPart(frames[1]));
		sprites.emplace_back(allCars.getPart(frames[2]));//UP_RIGHT
		sprites.emplace_back(allCars.getPart(frames[3]));
		sprites.emplace_back(allCars.getPart(frames[4]));//RIGHT

		sprites.emplace_back(allCars.getPart(frames[3]).rotateVertically());
		sprites.emplace_back(allCars.getPart(frames[2]).rotateVertically());//DOWN_RIGHT
		sprites.emplace_back(allCars.getPart(frames[1]).rotateVertically());
		sprites.emplace_back(allCars.getPart(frames[0]).rotateVertically());//DOWN

		sprites.emplace_back(allCars.getPart(frames[1]).rotateVertAndHor());
		sprites.emplace_back(allCars.getPart(frames[2]).rotateVertAndHor());//DOWN_LEFT
		sprites.emplace_back(allCars.getPart(frames[3]).rotateVertAndHor());

		sprites.emplace_back(allCars.getPart(frames[4]).rotateHorizontally());//LEFT
		sprites.emplace_back(allCars.getPart(frames[3]).rotateHorizontally());
		sprites.emplace_back(allCars.getPart(frames[2]).rotateHorizontally());//UP_LEFT
		sprites.emplace_back(allCars.getPart(frames[1]).rotateHorizontally());

		sprites.shrink_to_fit();
	}
	
	for (auto& v : directionVec)
	{
		v.normalize();
	}
	//make it start with 0 velocity
	vel = directionVec[dir];
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

//TODO: make it work on Vec
void Car::update()
{	
	pos += vel;
}

void Car::speedup(bool faster)
{
	//done wrong
	//TODO: do it using dot product
	float speedFactor = faster ? speed : -speed;
	const float actualVelSq = vel.getLengthSq();
	if(actualVelSq < maxVel * maxVel && actualVelSq > 0)
		vel +=  directionVec[dir] * speedFactor;
}

void Car::draw(Graphics & gfx) const
{
	drawCar(gfx);
}

void Car::reset()
{
	pos.x = config.getCarStartXPos();
	pos.y = config.getCarStartYPos();
	dir = config.getCarStartDir();
	//make it start with 0 velocity
	vel = directionVec[dir];
}

std::string Car::getDebugInfo() const
{
	std::stringstream ss;

	ss  << "x=" << pos.x << " y=" << pos.y 
	    << " velX=" << vel.x << " velY=" << vel.y 
		<< " maxVel=" << maxVel;

	return ss.str();
}

//TODO: different images for every car rotation
void Car::drawCar(Graphics & gfx) const
{
	gfx.drawSprite((Vei2)pos, sprites[dir]);
}