#include "Car.h"

Car::Car(int startX, int startY, Color c)
	:
	xPos(startX),
	yPos(startY),
	c(c)
{
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
}

void Car::speedup(bool faster)
{
	faster?
		velocity += speed:
		velocity -= speed;
}

void Car::draw(Graphics & gfx) const
{
	const float newWidth = (float)width / (float)sqrt(2);
	const float newHeight = (float)height / (float)sqrt(2);

	dir % 2 ?
		gfx.draw45Rect(xPos, yPos, newWidth, newHeight, c) :
		gfx.drawRectDim(xPos, yPos, width, height, c);
}
