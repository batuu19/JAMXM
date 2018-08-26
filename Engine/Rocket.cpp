#include "Rocket.h"

Rocket::Rocket(VecF2 pos, VecF2 vel, Surface sprite,int type)
	:
	pos(pos),
	vel(vel),
	sprite(sprite),
	type(type)
{
	switch (type)
	{
	case 0:
		attackValue = 30.f;
		break;
	case 1:
		attackValue = 60.f;
		break;
	default:
		break;
	}
}

void Rocket::draw(Graphics & gfx) const
{
	draw(gfx, { 0.f,0.f });
}

void Rocket::draw(Graphics & gfx, VecF2 cameraPos) const
{
	gfx.drawSprite(pos + cameraPos, sprite);
}

void Rocket::update(float dt)
{
	pos += vel * dt;
}

RectF Rocket::getHitbox() const
{
	return RectF(pos, sprite.getWidth(), sprite.getWidth());
}

const VecF2 & Rocket::getPosConst() const
{
	return pos;
}

int Rocket::getType() const
{
	return type;
}

int Rocket::getAttack() const
{
	return attackValue;
}
