#pragma once

#include "Graphics.h"
#include "BMath.h"
#include <vector>
#include "Surface.h"
#include "Directions.h"
#include "SpriteContainer.h"
#include <stdexcept>

//for car and rocket
//TODO: what about explosion and other?
class Entity
{
public:
	//Entity(const Entity&) = delete;

	virtual void update(float dt);
	void draw(Graphics&, VecF2 cameraPos) const;
	void reset();

	void damage(float amount);
	bool isDead() const;
	//TODO: fix - more accurate hitbox
	RectF getHitbox() const;
	const VecF2& getPosConst() const;
protected:
	Entity(VecF2 pos, int spriteState, SpriteContainer, VecF2 vel = { 0.f,0.f }, float HP = 300.f,float speed = 0.f, float maxVel = 0.f);

	VecF2 pos;
	VecF2 vel;
	const SpriteContainer sprites;
	float speed;
	float maxVel;
	int spriteState;
	float HP;
};