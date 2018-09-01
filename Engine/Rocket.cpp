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

BigRocket::BigRocket(VecF2 pos, int dir)
	:
	Rocket(pos, dir, (vectorsNormalized[dir] * 300.f), SpriteContainer({ "sprites//big_rocket_125x20.bmp" }, 5, 1, 25, 20), 100.f)
{
}

SmallRocket::SmallRocket(VecF2 pos, int dir)
	:
	Rocket(pos, dir, (vectorsNormalized[dir] * 500.f), SpriteContainer({ "sprites//small_rocket_175x35.bmp" }, 5, 1, 35, 35), 40.f)
{}

