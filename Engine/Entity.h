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
	Entity(VecF2 pos, std::string spriteFileName);

	void update();
	void draw(Graphics&) const;
	void getRect();
protected:
	VecF2 pos;
	SpriteContainer sprites;
	int dir;

	int width;
	int height;
};