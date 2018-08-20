#pragma once

#include "Graphics.h"
#include "BMath.h"
#include <vector>
#include "Surface.h"
#include "Directions.h"
#include "SpriteContainer.h"

//for car and rocket
//TODO: what about explosion and other?
class Entity
{
public:
	Entity(int x, int y, std::string spriteFileName);
	Entity(Config &);

protected:
	VecF2 pos;
	SpriteContainer sprites;
	int dir;

	int width;
	int height;
};