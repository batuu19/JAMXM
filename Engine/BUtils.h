#pragma once
#include <vector>

template<typename T>
void remove_element(std::vector<T>& vec, size_t index)
{
	// swap element to be removed with element at back
	std::swap(vec[index], vec.back());
	// back is now what we want dead, so pop back!
	vec.pop_back();
}

template<class Container, class Pred>
void remove_erase_if(Container& container, Pred pred)
{
	// this destroys all elements matching the predicate
	// and fills the spaces with elements from the end
	const auto new_end = std::remove_if(container.begin(), container.end(), pred);
	// erase garbage husk element at end
	container.erase(new_end, container.end());
}

template<typename T,typename S>
bool colliding(const T& first, const S& second)
{
	return first.getHitbox().isOverlappingWith(second.getHitbox());
}

template<typename T,typename S>
bool collidingWithBounds(const T& object, Rect<S> rect)
{
	return object.getHitbox().isContainedBy(rect);
}