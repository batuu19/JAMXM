#pragma once
#include "BMath.h"
#include "SpriteContainer.h"
#include "Graphics.h"
#include "Directions.h"
#include "SoundEffect.h"
#include "Entity.h"

class Rocket : public Entity
{
public:
	float getAttack() const;
	float getShootRate() const;
protected:
	Rocket(const VecF2& pos, int spriteState, const VecF2& vel,const SpriteContainer&, float attackValue, float shootRate);
	float attackValue;
	float shootRate;
};

class BigRocket : public Rocket
{
public:
	BigRocket(VecF2 pos,int dir);
};

class SmallRocket : public Rocket
{
public:
	SmallRocket(VecF2 pos,int dir);
};