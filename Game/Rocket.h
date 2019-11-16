#pragma once
#include "BMath.h"
#include "SpriteContainer.h"
#include "Graphics.h"
#include "Directions.h"
#include "SoundEffect.h"
#include "Entity.h"
#include "Animation.h"


//TODO static strings and values(static config?)
static constexpr char SPRITES_DIR[] = "sprites\\";
static constexpr char BIG_ROCKET_SPRITE[] = "sprites\\big_rocket_125x20.bmp";
static constexpr char BIG_EXPLOSION_SPRITE[] = "sprites\\big_explosion_336x55.bmp";
static constexpr char SMOKE_ANIM[] = "sprites\\smoke_anim.bmp";
static constexpr char SMALL_ROCKET_SPRITE[] = "sprites\\small_rocket_175x35.bmp";
static constexpr char SMALL_EXPLOSION_SPRITE[] = "sprites\\small_explosion_240x40.bmp";

class Rocket : public Entity
{
public:
	virtual ~Rocket() = default;
	float getAttack() const;
	virtual Animation getBoomAnim() const = 0;
	enum class Type
	{
		SmallRocket,
		BigRocket,
		None
	};
protected:
	Rocket(const VecF2& pos, int spriteState, const VecF2& vel,const SpriteContainer&, float attackValue);
	float attackValue;
	Sound sndShot = Sound(L"sound\\game\\rocketshot.wav");
};

class BigRocket : public Rocket
{
public:
	BigRocket(VecF2 pos,int dir,
		std::shared_ptr<std::vector<std::shared_ptr<Animation>>> animations);
	Animation getBoomAnim() const override;
	void update(float dt) override;
	
	static constexpr float shootRate = 0.45f;
private:
	std::shared_ptr<std::vector<std::shared_ptr<Animation>>> animations;
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