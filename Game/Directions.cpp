#include "Directions.h"

int getDirection(std::string name)
{
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);

	if (name == "up")
		return 0;
	else if (name == "up_right")
		return 2;
	else if (name == "right")
		return 4;
	else if (name == "down_right")
		return 6;
	else if (name == "down")
		return 8;
	else if (name == "down_left")
		return 10;
	else if (name == "left")
		return 12;
	else if (name == "up_left")
		return 14;
	else 
		return -1;
}
