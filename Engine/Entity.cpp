#include "Entity.h"

void Entity::update(float dt)
{
	pos += vel * dt;
}

void Entity::draw(Graphics & gfx, const VecF2& cameraPos) const
{
	if(!isDead())
		gfx.drawSprite(pos - cameraPos, sprites[spriteState]);
}

void Entity::reset()
{
	HP = maxHP;
}

bool Entity::damage(float amount)
{ 
	if(HP > 0)HP -= amount;
	return HP <= 0;
}

void Entity::kill()
{
	HP = 0;
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

Entity::Entity(const VecF2 & pos, int spriteState, const SpriteContainer & sprites, const VecF2 & vel, float HP, float speed, float maxVel)
	:
	pos(pos),
	vel(vel),
	spriteState(spriteState),
	sprites(sprites),
	speed(speed),
	maxVel(maxVel),
	HP(HP),
	maxHP(HP)
{
}

