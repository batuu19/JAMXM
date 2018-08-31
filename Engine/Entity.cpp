#include "Entity.h"

void Entity::update(float dt)
{
	pos += vel * dt;
}

void Entity::draw(Graphics & gfx, VecF2 cameraPos) const
{
	if(!isDead())
		gfx.drawSprite(pos - cameraPos, sprites[spriteState]);
}

void Entity::reset()
{
	HP = 300.f;
}

void Entity::damage(float amount)
{ 
	if(HP > 0)HP -= amount;
}

bool Entity::isDead() const
{
	return HP <= 0;
}

RectF Entity::getHitbox() const
{
	return RectF(pos, (float)sprites[spriteState].getWidth(), (float)sprites[spriteState].getHeight());
}

const VecF2 & Entity::getPosConst() const
{
	return pos;
}

Entity::Entity(VecF2 pos, int spriteState, SpriteContainer sprites, VecF2 vel, float HP, float speed, float maxVel)
	:
	pos(pos),
	vel(vel),
	spriteState(spriteState),
	sprites(sprites),
	speed(speed),
	maxVel(maxVel),
	HP(HP)
{
}
