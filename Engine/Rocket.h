#pragma once
#include "Config.h"
#include "BMath.h"
#include "SpriteContainer.h"
#include "Graphics.h"
#include "Directions.h"

class Rocket
{
public:
	Rocket(const Config&,int x, int y, int dir);
	Rocket(const Config&, VecF2 pos, int dir);

	void draw(Graphics&) const;
	void update();
private:
	VecF2 pos;
	VecF2 vel;
	int dir;

	//or do just one surface?
	SpriteContainer sprites;

};