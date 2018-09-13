#pragma once

#include <set>
#include <functional>
#include "BMath.h"
#include "Rect.h"

struct setPointsCompare {
	bool operator()(const VecI2& first, const VecI2& second) const
	{
		return first.y < second.y && first.x < second.x;
	}
};

class Hitbox {
public:
	Hitbox() = default;
	Hitbox(std::vector<VecI2>& pointsIn);

	virtual bool contains(const VecI2& point) const;
	virtual bool isOverlappingWith(const Hitbox& other) const;

protected:
	std::set < VecI2, setPointsCompare> points;
};

class RectHitbox : public Hitbox {
public:
	RectHitbox(const RectI& rectIn);

	bool isContainedBy(const RectHitbox& other) const;
	bool contains(const VecI2& point) const override;

	bool isOverlappingWith(const RectHitbox& other) const;
private:
	RectI rect;
};