#include "UFO.h"

UFO::UFO()
	:
	dirD(0, DIRECTIONS_COUNT-1),
	dir(dirD(rng))
{
}

void UFO::update(float dt)
{
	lastChanged += dt;
	if (lastChanged > changeDirectionTimer)
	{
		dir = dirD(rng);
		lastChanged = 0.f;
	}
	animTime += dt;
	if (animTime > animTimer)
	{
		activeFrame = (activeFrame + 1) % framesCount;
		animTime = 0.f;
	}
	pos += vectorsNormalized[dir] * vel * dt;
}

void UFO::draw(Graphics & gfx,const VecF2& cameraPos) const
{
	if(!dead)
		gfx.drawSprite(pos - cameraPos, sprite[activeFrame]);
}

void UFO::bounceBack()
{
	dir = getOpposite(dir);
	lastChanged = 0.f;
}

bool UFO::damage(float amount)
{
	HP -= amount;
	if (HP <= 0)
	{
		dead = true;
		return true;
	}
	else return false;
}

RectF UFO::getHitbox() const
{
	return RectF(pos, 70.f, 70.f);
}

bool UFO::isDead() const
{
	return dead;
}
