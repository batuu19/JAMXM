#pragma once
#include <vector>
#include <algorithm>

template<typename T, typename S>
bool attack(const T attacker, S defender)//return true if second is destroyed
{
	return defender->damage(attacker->getAttack());
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
