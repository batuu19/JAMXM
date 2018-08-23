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

void Rocket::update(float dt)
{
	pos += vel * dt;
}

const RectF & Rocket::getRect() const
{
	return RectF(pos, sprite.getWidth(), sprite.getWidth());
}

RectF Rocket::getHitbox() const
{
	return RectF(pos, sprite.getWidth(), sprite.getWidth());
}

const VecF2 & Rocket::getPosConst() const
{
	return pos;
}
