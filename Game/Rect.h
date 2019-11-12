#pragma once

#include "BMath.h"
#include <vector>

template<typename T>
class Rect
{
public:
	Rect() = default;
	Rect(T left_in, T right_in, T top_in, T bottom_in)
		:
		left(left_in),
		right(right_in),
		top(top_in),
		bottom(bottom_in)
	{
	}
	template<typename S>
	Rect(Rect<S> rhs)
		:
		left((T)rhs.left),
		right((T)rhs.right),
		top((T)rhs.top),
		bottom((T)rhs.bottom)
	{
	}
	Rect(const Vec2<T>& topLeft, const Vec2<T>& bottomRight)
		:
		Rect(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y)
	{
	}
	Rect(const Vec2<T>& topLeft, T width, T height)
		:
		Rect(topLeft, topLeft + Vec2<T>(width, height))
	{
	}
	bool isOverlappingWith(const Rect& other) const
	{
		return right > other.left&& left < other.right
			&& bottom > other.top&& top < other.bottom;
	}
	bool isContainedBy(const Rect& other) const
	{
		return left >= other.left && right <= other.right &&
			top >= other.top && bottom <= other.bottom;
	}
	bool contains(const Vec2<T> point) const
	{
		return left <= point.x && right >= point.x &&
			top <= point.y && bottom >= point.y;
	}
	bool contains(const Rect& other) const//unchecked
	{
		return left < other.left && right > other.right &&
			top < other.top && bottom > other.bottom;
	}
	static Rect fromCenter(const Vec2<T>& center, T halfWidth, T halfHeight)
	{
		const Vec2<T> half(halfWidth, halfHeight);
		return Rect(center - half, center + half);
	}
	Rect getExpanded(T offset) const
	{
		return Rect(left - offset, right + offset, top - offset, bottom + offset);
	}
	Rect getExpanded(T leftOffset, T rightOffset, T topOffset, T bottomOffset) const
	{
		return Rect(left - leftOffset, right + rightOffset, top - topOffset, bottom + bottomOffset);
	}
	Vec2<T> getCenter() const
	{
		return Vec2<T>((left + right) / (T)2, (top + bottom) / (T)2);
	}
	Vec2<T> getOrigin() const //top left corner
	{
		return Vec2<T>(left, top);
	}
	T getWidth() const
	{
		return right - left;
	}
	T getHeight() const
	{
		return bottom - top;
	}
	Rect& displaceBy(const Vec2<T>& d)
	{
		left += d.x;
		right += d.x;
		top += d.y;
		bottom += d.y;
		return *this;
	}
	Rect getDisplacedBy(const Vec2<T>& d) const
	{
		return Rect(*this).displaceBy(d);
	}
	Rect& moveTo0()
	{
		right -= left;
		left = 0;
		bottom -= top;
		top = 0;
		return *this;
	}
	Rect getMovedTo0() const
	{
		return Rect(*this).moveTo0();
	}
	Rect& fix()
	{
		if (left > right)
			std::swap(left, right);
		if (top > bottom)
			std::swap(top, bottom);
		return *this;
	}
	Rect getFixed() const
	{
		return Rect(*this).fix();
	}
	std::vector<Vec2<T>> getPoints()
	{
		std::vector<Vec2<T>> out;
		for (T y = left; y < right; y++)
		{
			for (T x = top; x < bottom; x++)
			{
				out.push_back(Vec2<T>(x, y));
			}
		}
		return out;
	}
public:
	T left;
	T right;
	T top;
	T bottom;
};

typedef Rect<int> RectI;
typedef Rect<float> RectF;
