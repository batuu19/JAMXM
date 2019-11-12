#include "Hitbox.h"

Hitbox::Hitbox(const std::vector<VecI2>& pointsIn)
{
	points.insert(pointsIn.begin(), pointsIn.end());
}

bool Hitbox::contains(const VecI2& point) const
{
	return points.find(point - pos) != points.end();
}

bool Hitbox::contains(const Hitbox & other) const
{
	//includes here?
	auto pos = other.pos;
	return std::all_of(other.points.begin(), other.points.end(), [&](VecI2 point) {
		return contains(point + pos);
	});
}

bool Hitbox::isOverlappingWith(const Hitbox & other) const
{
	for (auto p : other.points)
	{
		p -= other.pos;
		if (contains(p))
			return true;
	}
	return false;
}

void Hitbox::updatePos(const VecI2& newPos)
{
	pos = newPos;
}

void Hitbox::testDraw(Graphics & gfx, const VecF2 & cameraPos,Color c) const
{
	for (auto p : points)
	{
		p += pos - cameraPos;
		if (gfx.getScreenRect().getExpanded(-1).contains(p))
		{
			gfx.putPixel(p.x, p.y, c);
		}
	}
}

RectHitbox::RectHitbox(const RectI & rectIn)
	:
	Hitbox(rectIn.getMovedTo0().getPoints()),
	rect(rectIn.getMovedTo0())
{	
}

bool RectHitbox::isContainedBy(const RectHitbox & other) const
{
	return (rect.getDisplacedBy(pos).isContainedBy(other.rect));
}

bool RectHitbox::contains(const VecI2& point) const
{
	return rect.getDisplacedBy(pos).contains(point);
}

