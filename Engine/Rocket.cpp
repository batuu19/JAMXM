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
	Rocket(pos, dir, (vectorsNormalized[dir] * 400.f), SpriteContainer({ "sprites//big_rocket_125x20.bmp" }, 5, 1, 25, 20), 100.f)
{
}

Animation BigRocket::getBoomAnim() const
{
	return Animation(pos, "sprites\\big_explosion_336x55.bmp", 6, 336 / 6, 55);
}

void BigRocket::update(float dt)
{
	Rocket::update(dt);
	if (smokeOn)
	{
		smokeShowTime += dt;
		if (smokeShowTime > smokeShowTimer)
		{
			smokeOn = false;
			smokeShowTime = 0.f;
		}
			
		
	}
	smokeLastTime += dt;
	if (smokeLastTime > smokeTimer)
	{
		smokePos = pos;
		smokeOn = true;
		smokeLastTime = 0.f;
	}

}

void BigRocket::draw(Graphics & gfx, const VecF2 & cameraPos) const
{
	Rocket::draw(gfx, cameraPos);
	if (smokeOn)
		gfx.drawSprite(smokePos - cameraPos, smoke);
}

SmallRocket::SmallRocket(VecF2 pos, int dir)
	:
	Rocket(pos, dir, (vectorsNormalized[dir] * 550.f), SpriteContainer({ "sprites//small_rocket_175x35.bmp" }, 5, 1, 35, 35), 40.f)
{}

Animation SmallRocket::getBoomAnim() const
{
	return Animation(pos, "sprites\\small_explosion_240x40.bmp", 6, 240 / 6, 40);
}

