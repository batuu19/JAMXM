#pragma once
#include <vector>
#include <algorithm>

template<typename T, typename S>
bool colliding(const T first, const S second)
{
	return first->getHitbox().isOverlappingWith(second->getHitbox());
}

template<typename T, typename S>
bool collidingWithAny(const T first, const std::vector<S>& container)
{
	return std::any_of(container.begin(), container.end(),
		[&first](S obj)
	{
		return colliding(first, obj);
	})
}

template<typename T, typename S>
bool collidingWithBounds(const T object, Rect<S> rect)
{
	return object->getHitbox().isContainedBy(rect);
}

template<typename T, typename S>
bool collidingWithBoundsFixed(const T object, Rect<S> rect)
{
	return !object->getHitbox().isOverlappingWith(rect);
}

template<typename T,typename S>
bool isAllIn(const T object, const S in)
{
	return in->getHitbox().containsAll(*object);
}