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

	void draw(Graphics&) const;
	void update(float dt);
	const RectF& getRect() const;
private:
	VecF2 pos;
	VecF2 vel;
	//will not be compatibile with Entity
	Surface sprite;
};