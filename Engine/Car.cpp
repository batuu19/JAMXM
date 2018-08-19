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
	//TODO: make class for this
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

//TODO: make it work on Vec
void Car::update()
{

	vel.x = std::min(maxVel, std::max(-maxVel, vel.x));
	vel.y = std::min(maxVel, std::max(-maxVel, vel.y));

	pos += vel;
}

void Car::speedup(bool faster)
{
	//done wrong
	//TODO: do it using dot product
	float speedFactor = faster ? speed : -speed;

	switch (dir)
	{
	case 0://UP
		vel -= {0.0f,speedFactor};
		break;
	case 4://RIGHT
		vel += {speedFactor,0.0f};
		break;
	case 8://DOWN
		vel += {0.0f, speedFactor};
		break;
	case 12://LEFT
		vel -= {speedFactor, 0.0f};
		break;
	default:
		break;
	}
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