#include "UFO.h"

UFO::UFO(const VecF2& pos,std::mt19937& rng)
	:
	Entity(pos, 0, SpriteContainer({ "sprites\\ufo\\ufo3.bmp" }, 4, 2, false), { 0.f,0.f }, 400.f, 180.f),
	rng(rng),
	dirD(0, DIRECTIONS_COUNT - 1),
	dir(dirD(rng))
{
	vel = vectorsNormalized[dir] * speed;
}

void UFO::update(float dt)
{
	lastChanged += dt;
	if (lastChanged > changeDirectionTimer)
	{
		dir = dirD(rng);
		vel = vectorsNormalized[dir] * speed;
		lastChanged = 0.f;
	}
	animTime += dt;
	if (animTime > animTimer)
	{
		spriteState = (spriteState + 1) % framesCount;
		animTime = 0.f;
	}
	Entity::update(dt);
}

void UFO::bounceBack()
{
	dir = getOpposite(dir);
	vel = vectorsNormalized[dir] * speed;
}

float UFO::getAttack() const
{
	return attackValue;
}
