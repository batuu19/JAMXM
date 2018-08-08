#include "Car.h"

Car::Car(Config& config)
{
	xPos = (float)config.getCarStartXPos();
	yPos = (float)config.getCarStartYPos();
	velocity = config.getCarStartVelocity();
	speed = config.getCarSpeed();
	dir = config.getCarStartDir();
	c = config.getCarColor();
	maxVel = config.getCarMaxVelocity();

	turnRate = config.getCarTurnRate();
	leftTurn = 0.0f;
	rightTurn = 0.0f;
}

void Car::turnLeft()
{
	const float dt = ft.mark();
	if (leftTurn >= turnRate)
	{
		dir = (dir - 1 + DIRECTIONS_COUNT) % DIRECTIONS_COUNT;
		leftTurn = 0.0f;
	}
	leftTurn += dt;
}

void Car::turnRight()
{
	const float dt = ft.mark();

	if (rightTurn >= turnRate)
	{
		dir = (dir + 1) % DIRECTIONS_COUNT;
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

//TODO: 
void Car::drawCar(Graphics & gfx) const
{
	int padding = 5;
	Color paddingColor = Colors::Red;
	if (isSimpleDirection(dir))
	{
		int fixedX, fixedY, dX, dY;//delta X | delta Y

		//gfx.drawRectDim((int)xPos, (int)yPos, width, height, c);
		switch (dir)
		{
		case RIGHT:
			fixedX = xPos - width / 2;
			fixedY = yPos - height / 2;

			for (int y = fixedY; y < fixedY + height; y++)
			{
				int x = fixedX;
				while (x < fixedX + width - padding)
				{
					gfx.putPixel(x, y, c);
					x++;
				}
				while (x < fixedX + width)
				{
					gfx.putPixel(x, y, paddingColor);
					x++;
				}

			}

			break;
			
		case LEFT:
			fixedX = xPos + width / 2;
			fixedY = yPos - height / 2;

			for (int y = fixedY; y < fixedY + height; y++)
			{
				int x = fixedX;
				while (x > fixedX - width + padding)
				{
					gfx.putPixel(x, y, c);
					x--;
				}
				while (x > fixedX - width)
				{
					gfx.putPixel(x, y, paddingColor);
					x--;
				}

			}
			
			break;
		case DOWN:
			fixedX = xPos - width / 2;
			fixedY = yPos - height / 2;
			for (int x = fixedX; x < fixedX + width; x++)
			{
				int y = fixedY;
				while (y < fixedY + height - padding)
				{
					gfx.putPixel(x, y, c);
					y++;
				}
				while (y < fixedY + height)
				{
					gfx.putPixel(x, y, paddingColor);
					y++;
				}
			}

			break;
		case UP:
			fixedX = xPos - width / 2;
			fixedY = yPos + height / 2;

			for (int x = fixedX; x < fixedX + width; x++)
			{
				int y = fixedY;
				while (y > fixedY - height + padding)
				{
					gfx.putPixel(x, y, c);
					y--;
				}
				while (y > fixedY - height)
				{
					gfx.putPixel(x, y, paddingColor);
					y--;
				}
			}


			break;
		default:
			break;
		}

	}
	else
	{
		const int newWidth = (int)((float)width / (float)sqrt(2));
		const int newHeight = (int)((float)height / (float)sqrt(2));
		gfx.draw45Rect((int)xPos, (int)yPos, newWidth, newHeight, c);
		switch (dir)
		{
		case UP_RIGHT:
		{

			break;
		}
		case DOWN_RIGHT:

			break;

		case DOWN_LEFT:

			break;
		case UP_LEFT:

			break;
		default:
			break;
		}
	}
}