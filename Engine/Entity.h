#pragma once

#include "Graphics.h"
#include "BMath.h"
#include <vector>
#include "Surface.h"
#include "Directions.h"
#include "SpriteContainer.h"
#include <stdexcept>

//for car and rocket
//TODO: what about explosion and other?
class Entity
{
public:
	Entity(VecF2 pos,
		std::string spriteFileName, int spriteWidth, int spriteHeight, int spritesRows = 5, int spritesLines = 1);
	Entity(VecF2 pos,int dir,
		std::string spriteFileName, int spriteWidth, int spriteHeight, int spritesRows = 5, int spritesLines = 1);

	void update();
	void draw(Graphics&) const;
	RectF getRect();
protected:
	VecF2 pos;
	const SpriteContainer sprites;
	int dir;

	int width;
	int height;
};