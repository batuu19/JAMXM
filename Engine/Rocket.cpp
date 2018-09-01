#include "Rocket.h"

float Rocket::getAttack() const
{
	return attackValue;
}

float Rocket::getShootRate() const
{
	return shootRate;
}

Rocket::Rocket(const VecF2& pos,int spriteState, const VecF2& vel, const SpriteContainer& sprites, float attackValue,float shootRate)
	:
	Entity(pos, spriteState, sprites,vel),
	attackValue(attackValue),
	shootRate(shootRate)
{
}

BigRocket::BigRocket(VecF2 pos, int dir)
	:
	Rocket(pos, dir, (vectorsNormalized[dir] * 700.f), SpriteContainer({ "sprites//big_rocket_125x20.bmp" }, 5, 1, 25, 20),40.f,0.23f)
{
}

SmallRocket::SmallRocket(VecF2 pos, int dir)
	:
	Rocket(pos, dir, (vectorsNormalized[dir] * 400.f), SpriteContainer({ "sprites//small_rocket_175x35.bmp" }, 5, 1, 35, 35),100.f,0.45f )
{}

