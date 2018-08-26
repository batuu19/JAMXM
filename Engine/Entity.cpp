#include "Entity.h"


Entity::Entity(VecF2 pos, std::string spriteFileName, int spriteWidth, int spriteHeight, int spritesRows, int spritesLines)
	:
	pos(pos),
	sprites(spriteFileName, spritesRows, spritesLines, spriteWidth, spriteHeight),
	dir(0)
{
}

Entity::Entity(VecF2 pos, int dir, std::string spriteFileName, int spriteWidth, int spriteHeight, int spritesRows, int spritesLines)
	:
	pos(pos),
	sprites(spriteFileName, spritesRows, spritesLines, spriteWidth, spriteHeight),
	dir(dir)
{
}

void Entity::update(float dt)
{
	if (sprites.getSize() < 0)throw std::exception("no sprites");
	if (dir > sprites.getSize())throw std::exception("wrong dir");
}

void Entity::draw(Graphics & gfx) const
{
	draw(gfx, { 0.f,0.f });
}

void Entity::draw(Graphics & gfx, VecF2 cameraPos) const
{
	if(!dead)
		gfx.drawSprite(pos - cameraPos, sprites[dir]);
}

void Entity::reset()
{
	HP = 300.f;
	dead = false;
}

void Entity::damage(float amount)
{
	HP -= amount;
	if (HP <= 0.f)
		dead = true;
}

bool Entity::isDead() const
{
	return dead;
}

RectF Entity::getHitbox() const
{
	return RectF(pos, (float)sprites[dir].getWidth(), (float)sprites[dir].getHeight());
}
