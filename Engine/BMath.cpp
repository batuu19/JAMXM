#include "BMath.h"

Hitbox::Hitbox(std::vector<VecI2>& points)
	:
	points(std::move(points))
{
}

bool Hitbox::contains(VecI2 point)
{
	return std::any_of(points.begin(), points.end(), [&](VecI2 second) {return point == second; });
}

bool Hitbox::isOverlappingWith(const Hitbox & second)
{
	for (auto& p : second.points)
	{
		if(contains(p))
			return true;
	}
	return false;
}
