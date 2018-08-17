#include "Car.h"

Car::Car(Config& config)
	:
	xPos((float)config.getCarStartXPos()),
	yPos((float)config.getCarStartYPos()),
	velocity(config.getCarStartVelocity()),
	speed(config.getCarSpeed()),
	maxVel(config.getCarMaxVelocity()),
	dir(config.getCarStartDir()),
	sprites(config.getCarImageFileName()),
	turnRate(config.getCarTurnRate())
{
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

void Car::update()
{
	bool isSimpleDir = !(dir % 2);

	if (isSimpleDir)
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
	else
	{
		//round up? (ceil)
		int newVelocity = (int)(velocity / sqrt(2) );
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
	RectI srcRect;
	switch (dir)
	{
	case 0://UP
		srcRect = { 0,70,0,70 };
		break;
	case 1:
		srcRect = { 70,140,0,70 };
		break;
	case 2://UP_RIGHT
		srcRect = { 140,210,0,70 };
		break;
	case 3:
		srcRect = { 210,280,0,70 };
		break;

	default:
		srcRect = { 0,70,0,70 };
		break;
	}
	gfx.drawSprite(xPos, yPos, srcRect, sprites);
}