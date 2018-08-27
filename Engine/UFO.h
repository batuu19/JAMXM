#pragma once
#include "Rect.h"
#include "BMath.h"
#include "Graphics.h"
#include <random>
#include "Directions.h"
#include "SpriteContainer.h"

class UFO
{
public:
	UFO();
	void update(float dt);
	void draw(Graphics&,const VecF2& cameraPos) const;

	void bounceBack();
	bool damage(float amount);//return true if destroyed
	RectF getHitbox() const;
	bool isDead() const;

private:
	std::mt19937 rng = std::mt19937(std::random_device{}());
	std::uniform_int_distribution<int> dirD;
	VecF2 pos = { 500.f,200.f };
	float vel = 80.f;
	int dir;
	float HP = 400.f;
	bool dead = false;

	float changeDirectionTimer = 4.f;
	float lastChanged = 0.f;
	float animTimer = 0.1f;
	float animTime = 0.f;
	int framesCount = 8;
	int activeFrame = 0;
	SpriteContainer sprite = SpriteContainer({ "sprites\\ufo\\ufo3.bmp"},4,2,80,80,false );
};