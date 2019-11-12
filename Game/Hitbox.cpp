#include "Hitbox.h"

Hitbox::Hitbox(const RectI& rect, VecI2 pos)
	:
	rect(rect),
	pos(pos)
{
}

Hitbox::Hitbox(const RectI& rect)
	:
	Hitbox(rect.getMovedTo0(),rect.getOrigin())
{
}

bool Hitbox::contains(const VecI2& point) const
{
	return getFixedRect().contains(point);
}

bool Hitbox::contains(const RectI& other) const
{
	return getFixedRect().contains(other);
}

bool Hitbox::contains(const Hitbox& other) const
{
	return getFixedRect().contains(other.getFixedRect());
}

bool Hitbox::isOverlappingWith(const Hitbox& other) const
{
	return getFixedRect().isOverlappingWith(other.getFixedRect());
}

bool Hitbox::isContainedBy(const Hitbox& other) const
{
	return getFixedRect().isContainedBy(other.getFixedRect());
}

bool Hitbox::isContainedBy(const RectI& other) const
{
	return getFixedRect().isContainedBy(other);
}

void Hitbox::updatePos(const VecI2& newPos)
{
	pos = newPos;
}

RectI Hitbox::getFixedRect() const
{
	return rect.getDisplacedBy(pos);
}
