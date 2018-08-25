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
	gfx.drawSprite(pos + cameraPos, sprites[dir]);
}

const RectF& Entity::getRect() const
{
	return RectF(pos, sprites[dir].getWidth(), sprites[dir].getHeight());
}

RectF Entity::getHitbox() const
{
	return RectF(pos, sprites[dir].getWidth(), sprites[dir].getHeight());
}
