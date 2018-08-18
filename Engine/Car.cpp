#include "Car.h"

Car::Car(Config& config)
	:
	xPos((float)config.getCarStartXPos()),
	yPos((float)config.getCarStartYPos()),
	velocity(config.getCarStartVelocity()),
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
	bool isSimpleDir = !(dir % 2);

	if (dir % 4 == 0)
	{
		switch (dir)
		{
		case UP:
			yPos -= (int)velocity;
			break;
		case RIGHT:
			xPos += (int)velocity;
			break;
		case DOWN:
			yPos += (int)velocity;
			break;
		case LEFT:
			xPos -= (int)velocity;
			break;
		default:
			break;
		}
	}
	else if(dir % 2 == 0)
	{
		//round up? (ceil)
		//TODO: simplify?
		float newVelocity = velocity / sqrt(2) ;
		switch (dir)
		{
		case UP_RIGHT:
			yPos -= newVelocity;
			xPos += newVelocity;
			break;
		case DOWN_RIGHT:
			xPos += newVelocity;
			yPos += newVelocity;
			break;
		case DOWN_LEFT:
			yPos += newVelocity;
			xPos -= newVelocity;
			break;
		case UP_LEFT:
			xPos -= newVelocity;
			yPos -= newVelocity;
			break;
		default:
			break;
		}
	}
	else
	{
		//TODO: simplify?
		float newVelocity = velocity * 2 / sqrt(5);
		switch (dir)
		{

		case 1:
			xPos += newVelocity / 2;
			yPos -= newVelocity;
			break;
		case 3:
			xPos += newVelocity;
			yPos -= newVelocity / 2;
			break;
		case 5:
			xPos += newVelocity;
			yPos += newVelocity / 2;
			break;
		case 7:
			xPos += newVelocity / 2;
			yPos += newVelocity;
			break;
		case 9:
			xPos -= newVelocity / 2;
			yPos += newVelocity;
			break;
		case 11:
			xPos -= newVelocity;
			yPos += newVelocity / 2;
			break;
		case 13:
			xPos -= newVelocity;
			yPos -= newVelocity / 2;
			break;
		case 15:
			xPos -= newVelocity / 2;
			yPos -= newVelocity;
			break;
		default:
			break;
		}
	}

	velocity = std::min(maxVel, std::max(0.0f,velocity));

}

void Car::speedup(bool faster)
{
	faster?
		velocity += speed:
		velocity -= speed;
}

void Car::draw(Graphics & gfx) const
{
	drawCar(gfx);
}

std::string Car::getDebugInfo() const
{
	std::stringstream ss;

	ss << "x=" << xPos << " y=" << yPos << " vel=" << velocity << " maxVel=" << maxVel;

	return ss.str();
}

//TODO: different images for every car rotation
void Car::drawCar(Graphics & gfx) const
{
	gfx.drawSprite(xPos, yPos, sprites[dir]);
}