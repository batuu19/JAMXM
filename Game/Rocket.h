#pragma once
#include "BMath.h"
#include "SpriteContainer.h"
#include "Graphics.h"
#include "Directions.h"
#include "SoundEffect.h"
#include "Entity.h"
#include "Animation.h"

class Rocket : public Entity
{
public:
	float getAttack() const;
	virtual Animation getBoomAnim() const = 0;
protected:
	Rocket(const VecF2& pos, int spriteState, const VecF2& vel,const SpriteContainer&, float attackValue);
	float attackValue;
};

class BigRocket : public Rocket
{
public:
	BigRocket(VecF2 pos,int dir,std::vector<Animation>&);
	Animation getBoomAnim() const override;
	void update(float dt) override;
	
	static constexpr float shootRate = 0.45f;
private:
	std::vector<Animation>& animations;
	float smokeTimer = 0.14f;
	float smokeLastTime = 0.f;
};

class SmallRocket : public Rocket
{
public:
	SmallRocket(VecF2 pos,int dir);
	Animation getBoomAnim() const override;


	static constexpr float shootRate = 0.23f;
};