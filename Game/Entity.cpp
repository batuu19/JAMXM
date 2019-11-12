#include "Entity.h"

void Entity::update(float dt)
{
	if (invincible) 
	{
		invincibleTime += dt;
		if (invincibleTime > invincibleTimer)
		{
			invincible = false;
			invincibleTime = 0.f;
		}
	}
	pos += vel * dt;

	for (auto& h : hitbox)
	{
		h.updatePos(pos);
	}
}

void Entity::draw(Graphics & gfx, const VecF2& cameraPos) const
{
	if (!isDead())
	{
		if ((int)(invincibleTime * 20.f) % 4 == 0)
			gfx.drawSprite(pos - cameraPos, sprites[spriteState]);
	}
}

void Entity::reset()
{
	HP = maxHP;
}

bool Entity::damage(float amount)
{
	if (HP > 0 && !invincible)
	{
		HP -= amount;
		invincible = true;
	}
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

const Hitbox& Entity::getHitbox() const
{
	return hitbox[spriteState];
}

const VecF2 & Entity::getPosConst() const
{
	return pos;
}

Entity::Entity(const VecF2 & pos, int spriteState, const SpriteContainer & sprites, 
	const VecF2 & vel, float HP, float speed, float maxVel,
	float invincibilityTime, bool invincibleAtStart
	)
	:
	pos(pos),
	vel(vel),
	spriteState(spriteState),
	sprites(sprites),
	speed(speed),
	maxVel(maxVel),
	HP(HP),
	maxHP(HP),
	invincibleTimer(invincibilityTime),
	invincible(invincibleAtStart)
{
	for (auto& s : sprites)
	{
		auto points = s.getHitablePoints();
		hitbox.emplace_back(points);
	}
}

