#include "Rocket.h"

Rocket::Rocket(VecF2 pos, VecF2 vel, Surface sprite)
	:
	pos(pos),
	vel(vel),
	sprite(sprite)
{
}

void Rocket::draw(Graphics & gfx) const
{
	gfx.drawSprite((VecI2)pos, sprite);
}

void Rocket::update()
{
	pos += vel;
}
