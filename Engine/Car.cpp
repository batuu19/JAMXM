#include "Car.h"

Car::Car(int startX, int startY, Color c)
	:
	xPos(startX),
	yPos(startY),
	c(c)
{
	velocity = 1.0f;
	dir = Direction::Right;
}

void Car::update(Direction newDir)
{
	dir = newDir;
}

void Car::update()
{

}

void Car::draw(Graphics & gfx) const
{
	gfx.drawRectDim(xPos, yPos, width, height, c);
}
