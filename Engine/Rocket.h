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
	BigRocket(VecF2 pos,int dir);
	Animation getBoomAnim() const override;
	void update(float dt) override;
	void draw(Graphics &, const VecF2& cameraPos) const override;
	
	static constexpr float shootRate = 0.45f;
private:
	VecF2 smokePos;
	float smokeTimer = 0.4f;
	float smokeLastTime = 0.f;
	float smokeShowTimer = 0.25f;
	float smokeShowTime = 0.f;
	bool smokeOn = false;
	Surface smoke = "sprites\\smoke.bmp";
};

class SmallRocket : public Rocket
{
public:
	SmallRocket(VecF2 pos,int dir);
	Animation getBoomAnim() const override;


	static constexpr float shootRate = 0.23f;
};