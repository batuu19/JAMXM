#pragma once
#include "BMath.h"
#include "SpriteContainer.h"
#include "Graphics.h"
#include "Directions.h"
#include "SoundEffect.h"

class Rocket
{
public:
	Rocket(VecF2 pos,VecF2 vel, Surface sprite);
	Rocket(const Rocket&) = delete;
	Rocket(Rocket&&) = default;
	Rocket& operator=(const Rocket&) = default;

	void draw(Graphics&) const;
	void draw(Graphics&, VecF2 cameraPos) const;
	void update(float dt);

	const RectF& getRect() const;
	//TODO: fix - more accurate hitbox
	RectF getHitbox() const;
	const VecF2& getPosConst() const;
private:
	VecF2 pos;
	VecF2 vel;
	//will not be compatibile with Entity
	Surface sprite;
};