#include "Config.h"

Config::Config(std::string filename)
{
	std::fstream in(filename);

	for (std::string line; std::getline(in, line);)
	{
		if (line == "[Car start pos]")
		{
			in >> carStartXPos >> carStartYPos ;
		}
		else if (line == "[Car start direction]")
		{
			std::string dir;
			in >> dir;
			carStartDir = getDirection(dir);
		}
		else if (line == "[Car start velocity]")
		{
			in >> carStartVelocity;
		}
		else if (line == "[Car speed]")
		{
			in >> carSpeed;
		}
		else if (line == "[Car max velocity]")
		{
			in >> carMaxVelocity;
		}
		else if (line == "[Car turn rate]")
		{
			in >> carTurnRate;
		}
		else if (line == "[Map file name]")
		{
			in >> mapFileneme;
		}
		else if (line == "[Car color]")
		{
			int r, g, b;
			in >> r >> g >> b;
			carColor = Color(r, g, b);
		}
		else
		{
			//TODO: do this?
			//throw std::runtime_error("Bad line in settings file: " + line);
		}
	}
}

int Config::getCarStartXPos() const
{
	return carStartXPos;
}

int Config::getCarStartYPos() const
{
	return carStartYPos;
}

int Config::getCarStartDir() const
{
	return carStartDir;
}

float Config::getCarStartVelocity() const
{
	return carStartVelocity;
}

float Config::getCarSpeed() const
{
	return carSpeed;
}

float Config::getCarMaxVelocity() const
{
	return carMaxVelocity;
}

float Config::getCarTurnRate() const
{
	return carTurnRate;
}

Color Config::getCarColor() const
{
	return carColor;
}

std::string Config::getMapFilename() const
{
	return mapFileneme;
}
