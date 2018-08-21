#pragma once
#include <fstream>
#include <string>
#include "Directions.h"
#include "Colors.h"

class Config
{
public:
	Config(std::string filename);

	//Car
	int carStartXPos;
	int carStartYPos;
	int carStartDir;

};

