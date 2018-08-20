#pragma once

#include "Graphics.h"
#include "BMath.h"
#include <vector>
#include "Surface.h"
#include "Directions.h"

//for car and rocket
//TODO: what about explosion and other?
class Entity
{
public:

protected:
	VecF2 pos;
	std::vector<Surface> sprites;
	int dir;
};