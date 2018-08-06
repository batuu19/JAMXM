#include "Car.h"

Car::Car(int startX, int startY, Color c)
	:
	xPos(startX),
	yPos(startY),
	c(c)
{
	velocity = 0.0f;
	speed = 0.4f;
	dir = RIGHT;
}

void Car::turnLeft()
{
	dir = (dir - 1 + DIRECTIONS_COUNT) % DIRECTIONS_COUNT;
}

void Car::turnRight()
{
	dir = (dir + 1) % DIRECTIONS_COUNT;
}


void Car::update()
{
	switch (dir)
	{
	case UP:
		yPos -= (int)velocity;
		break;
	case UP_RIGHT:
		yPos -= (int)velocity;
		xPos += (int)velocity;
		break;
	case RIGHT:
		xPos += (int)velocity;
		break;
	case DOWN_RIGHT:
		xPos += (int)velocity;
		yPos += (int)velocity;
		break;
	case DOWN:
		yPos += (int)velocity;
		break;
	case DOWN_LEFT:
		yPos += (int)velocity;
		xPos -= (int)velocity;
		break;
	case LEFT:
		xPos -= (int)velocity;
		break;
	case UP_LEFT:
		xPos -= (int)velocity;
		yPos -= (int)velocity;
		break;
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
	const float newWidth = (float)width * (float)sqrt(2) / 2.0f;
	const float newHeight = (float)height * (float)sqrt(2) / 2.0f;

	dir % 2 ?
		gfx.draw45Rect(xPos, yPos, newWidth, newHeight, c) :
		gfx.drawRectDim(xPos, yPos, width, height, c);
}
