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
	}
}