#pragma once
#include "Rect.h"
#include "BMath.h"
#include "Graphics.h"
#include <random>
#include "Directions.h"
#include "SpriteContainer.h"
#include "Entity.h"

class UFO : public Entity
{
public:
	UFO(const VecF2& pos,std::mt19937& rng);
	void update(float dt) override;

	void bounceBack();

private:
	mutable std::mt19937 rng;
	mutable std::uniform_int_distribution<int> dirD;

	float changeDirectionTimer = 4.f;
	float lastChanged = 0.f;
	float animTimer = 0.1f;
	float animTime = 0.f;
	int framesCount = 8;
	int activeFrame = 0;

	int dir;
};