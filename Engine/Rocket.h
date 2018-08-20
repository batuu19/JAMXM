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
	Rocket(const Config&, Vec2 pos, int dir);

	void draw(Graphics&) const;
	void update();
private:
	Vec2 pos;
	Vec2 vel;
	int dir;

	//or do just one surface?
	SpriteContainer sprites;

};