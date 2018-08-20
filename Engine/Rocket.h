#pragma once
#include "BMath.h"
#include "SpriteContainer.h"
#include "Graphics.h"
#include "Directions.h"

class Rocket
{
public:
	Rocket(VecF2 pos,VecF2 vel, Surface sprite);

	void draw(Graphics&) const;
	void update();
private:
	VecF2 pos;
	VecF2 vel;
	Surface sprite;

};