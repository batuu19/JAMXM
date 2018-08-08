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

	//loading image
	//TODO: class for images
	std::string filename = config.getCarImageFileName();

	std::ifstream file(filename, std::ios::binary);

	BITMAPFILEHEADER bmFileHeader;
	file.read(reinterpret_cast<char*>(&bmFileHeader), sizeof(bmFileHeader));

	BITMAPINFOHEADER bmInfoHeader;
	file.read(reinterpret_cast<char*>(&bmInfoHeader), sizeof(bmInfoHeader));

	assert(bmInfoHeader.biBitCount == 24);
	assert(bmInfoHeader.biCompression == BI_RGB);

	width = bmInfoHeader.biWidth;
	height = bmInfoHeader.biHeight;

	pPixels = new Color[width * height];

	file.seekg(bmFileHeader.bfOffBits);
	const int padding = (4 - (width * 3) % 4) % 4;


	//TODO: better loading, from car's back to front
	for (int y = height - 1; y >= 0; y--)
	{
		for (int x = 0; x < width; x++)
		{
			pPixels[y* width + x] = Color(file.get(), file.get(), file.get());
		}
		file.seekg(padding, std::ios::cur);
	}
}

Car::Car(const Car & rhs)
	:
	xPos(rhs.xPos),
	yPos(rhs.yPos),
	velocity(rhs.velocity),
	speed(rhs.speed),
	maxVel(rhs.maxVel),
	dir(rhs.dir),
	c(rhs.c),
	width(rhs.width),
	height(rhs.height),
	pPixels(new Color[width * height]),
	ft(rhs.ft),
	turnRate(rhs.turnRate)

{
	const int nPixels = width * height;
	for (int i = 0; i < nPixels; i++)
	{
		pPixels[i] = rhs.pPixels[i];
	}
}


Car::~Car()
{
	delete[] pPixels;
	pPixels = nullptr;
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

//TODO: 
void Car::drawCar(Graphics & gfx) const
{
	int padding = 5;
	Color paddingColor = Colors::Red;
	if (isSimpleDirection(dir))
	{
		//warning conversion from float to int
		for (int i = 0; i < height; i++)//y
		{
			for (int j = 0; j < width; j++)//x
			{
				//switch here? and if
				switch (dir)
				{
				case UP:
					gfx.putPixel(j + xPos,height - i + yPos , pPixels[i * width + j]);
					break;
				case RIGHT:
					gfx.putPixel(i + xPos, j + yPos, pPixels[i * width + j]);
					break;
				case LEFT:
					gfx.putPixel(width - i + xPos, j + yPos, pPixels[i * width + j]);
					break;
				case DOWN:
					gfx.putPixel(j + xPos, i + yPos, pPixels[i * width + j]);
					break;
				default:
					break;
				}
			}
		}
	

	}
	//TODO: NOT SIMPLE DIRECTIONS TO DO
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