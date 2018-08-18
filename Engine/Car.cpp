#include "Car.h"

Car::Car(Config& config)
	:
	pos(config.getCarStartXPos(), config.getCarStartYPos()),
	vel(config.getCarStartVelocity(), config.getCarStartVelocity()),
	speed(config.getCarSpeed()),
	maxVel(config.getCarMaxVelocity()),
	dir(config.getCarStartDir()),
	turnRate(config.getCarTurnRate())
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

void Car::turnLeft()
{
	const float dt = ft.mark();
	if (leftTurn >= turnRate)
	{
		dir = (dir - turnValue + DIRECTIONS_COUNT) % DIRECTIONS_COUNT;
		leftTurn = 0.0f;
	}
	leftTurn += dt;
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
}

//TODO: simplify
void Car::update()
{
	pos += vel;

	vel.x = std::min(maxVel, std::max(0.0f, vel.x));
	vel.y = std::min(maxVel, std::max(0.0f, vel.y));

}

void Car::speedup(bool faster)
{
	faster?
		vel *= speed:
		vel *= 1.0f - speed;
}

void Car::draw(Graphics & gfx) const
{
	drawCar(gfx);
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