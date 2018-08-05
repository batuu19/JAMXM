#include "Car.h"

Car::Car(int startX, int startY, Color c)
	:
	xPos(startX),
	yPos(startY),
	c(c)
{
	velocity = 2.0f;
	speed = 0.4f;
	dir = RIGHT;
}

void Car::turnLeft()
{
	dir = (dir - 2 + DIRECTIONS_COUNT) % DIRECTIONS_COUNT;
}

void Car::turnRight()
{
	dir = (dir + 2) % DIRECTIONS_COUNT;
}


void Car::update()
{
	switch (dir)
	{
	case RIGHT:
		xPos += (int)velocity;
		break;
	case DOWN:
		yPos += (int)velocity;
		break;
	case LEFT:
		xPos -= (int)velocity;
		break;
	case UP:
		yPos -= (int)velocity;
	default:
		break;
	}
}

void Car::speedup(bool faster)
{
	faster?
		velocity += speed:
		velocity -= speed;
}

void Car::draw(Graphics & gfx) const
{
	gfx.drawRectDim(xPos, yPos, width, height, c);
}
