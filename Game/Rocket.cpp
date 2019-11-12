#include "Rocket.h"

float Rocket::getAttack() const
{
	return attackValue;
}

Rocket::Rocket(const VecF2& pos,int spriteState, const VecF2& vel, const SpriteContainer& sprites, float attackValue)
	:
	Entity(pos, spriteState, sprites,vel),
	attackValue(attackValue)
{
}

BigRocket::BigRocket(VecF2 pos, int dir,std::vector<Animation>& animations)
	:
	Rocket(pos, dir, (vectorsNormalized[dir] * 400.f), SpriteContainer({ BIG_ROCKET_SPRITE }, 5, 1), 100.f),
	animations(animations)
{
}

Animation BigRocket::getBoomAnim() const
{
	return Animation(pos, BIG_EXPLOSION_SPRITE, 6, 336 / 6, 55);
}

void BigRocket::update(float dt)
{
	Rocket::update(dt);
	smokeLastTime += dt;
	if (smokeLastTime > smokeTimer)
	{
		animations.emplace_back(pos, SMOKE_ANIM, 4, 27, 23);
		smokeLastTime = 0.f;
	}

}

SmallRocket::SmallRocket(VecF2 pos, int dir)
	:
	Rocket(pos, dir, (vectorsNormalized[dir] * 550.f), SpriteContainer({ SMALL_ROCKET_SPRITE }, 5, 1, 35, 35), 40.f)
{}

Animation SmallRocket::getBoomAnim() const
{
	return Animation(pos, SMALL_EXPLOSION_SPRITE, 6, 240 / 6, 40);
}