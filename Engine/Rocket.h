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
	Rocket(VecF2 pos, int spriteState, VecF2 vel, SpriteContainer sprites, float attackValue, float shootRate);
protected: 
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