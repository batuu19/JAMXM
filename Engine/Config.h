#pragma once
#include <fstream>
#include <string>
#include "Directions.h"
#include "Colors.h"

class Config
{
public:
	Config(std::string filename);
	
	int getCarStartXPos() const;
	int getCarStartYPos() const;
	int getCarStartDir() const;
	float getCarStartVelocity() const;
	float getCarSpeed() const;
	float getCarMaxVelocity() const;
	float getCarTurnRate() const;
	Color getCarColor() const;
	std::string getCarImageFileName() const;

	std::string getMapFilename() const;
	
private:

	//Car
	int carStartXPos;
	int carStartYPos;
	int carStartDir;
	float carStartVelocity;
	float carSpeed;
	float carMaxVelocity;
	float carTurnRate;
	Color carColor;
	std::string  carImageFileName;

	//Map
	std::string mapFileneme;

};

