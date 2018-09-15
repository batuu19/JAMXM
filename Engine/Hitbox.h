#pragma once

#include <set>
#include <functional>
#include "BMath.h"
#include "Rect.h"
#include "Graphics.h"

struct setPointsCompare {
	bool operator()(const VecI2& first, const VecI2& second) const
	{
		if (first.x < second.x)return true;
		if (first.x > second.x)return false;
		if (first.y < second.y)return true;
		if (first.y > second.y)return false;
		return false;
	}
};

class Hitbox {
public:
	Hitbox() = default;
	Hitbox(const Hitbox&) = delete;
	Hitbox(const std::vector<VecI2>& pointsIn);

	virtual bool contains(const VecI2& point) const;
	template<typename T>
	bool containsAll(const T& object) const;
	virtual bool isOverlappingWith(const Hitbox& other) const;
	virtual void updatePos(const VecI2& newPos);


	void testDraw(Graphics&, const VecF2& cameraPos,Color c = Colors::Red) const;
protected:
	std::set < VecI2, setPointsCompare> points;
	VecI2 pos;//top left
private:
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

template<typename T>
inline bool Hitbox::containsAll(const T & object) const
{
	const auto& hitbox = object.getHitbox();
	return !std::any_of(points.begin(), points.end(), [&](const VecI2& point)
	{
		return hitbox.contains(point);
	});
}
