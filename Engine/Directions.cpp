#include "Directions.h"

bool isSimpleDirection(int direction)
{
	return !(direction % 2);
}

int getDirection(std::string name)
{
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);

	if (name == "up")
		return 0;
	else if (name == "up_right")
		return 1;
	else if (name == "right")
		return 2;
	else if (name == "down_right")
		return 3;
	else if (name == "down")
		return 4;
	else if (name == "down_left")
		return 5;
	else if (name == "left")
		return 6;
	else if (name == "up_left")
		return 7;
	else 
		return -1;
}
