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
bool attack(const T& attacker, S& defender)//return true if second is destroyed
{
	return defender.damage(attacker.getAttack());
}

template<typename T,typename S>
bool collidingWithBounds(const T& object, Rect<S> rect)
{
	return object.getHitbox().isContainedBy(rect);
}

inline void makeBigBoom(int amount, const VecI2& center,int range, std::mt19937& rng,std::vector<Animation>& animations)
{
	std::uniform_int_distribution<int> xD(-range,range),yD(-range,range);

	auto getAnim = [](int x,int y) { return Animation({ x,y },"sprites\\big_explosion_336x55.bmp", 6, 336 / 6, 55); };

	for (int i = 0; i < amount; i++)
	{
		animations.push_back(getAnim(center.x + xD(rng), center.y + yD(rng)));
	}
}