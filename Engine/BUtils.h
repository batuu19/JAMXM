#pragma once
#include <vector>

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
bool checkCollision(const T& first, const S& second)
{
	return first.getHitbox().isOverlappingWith(second.getHitbox());
}