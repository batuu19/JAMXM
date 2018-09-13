#include "Hitbox.h"

Hitbox::Hitbox(std::vector<VecI2>& pointsIn)
{
	points.insert(pointsIn.begin(), pointsIn.end());
}

bool Hitbox::contains(const VecI2& point) const
{
	auto data = points.find(point);
	return data == points.end();
}

bool Hitbox::isOverlappingWith(const Hitbox & other) const
{
	for (auto& p : other.points)
	{
		if (contains(p))
			return true;
	}
	return false;
}

RectHitbox::RectHitbox(const RectI & rectIn)
	:
	Hitbox(rectIn.getMovedTo0().getPoints()),
	rect(rectIn.getMovedTo0())
{	
}

bool RectHitbox::isContainedBy(const RectHitbox & other) const
{
	return (rect.isContainedBy(other.rect));
}

bool RectHitbox::contains(const VecI2& point) const
{
	return rect.contains(point);
}

bool RectHitbox::isOverlappingWith(const RectHitbox & other) const
{
	return rect.isOverlappingWith(other.rect);
}

