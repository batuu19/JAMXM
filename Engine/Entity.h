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
	virtual ~Entity() = default;

	virtual void update(float dt);
	virtual void draw(Graphics&, const VecF2& cameraPos) const;
	void reset();

	bool damage(float amount);//return true if destroyed
	void kill();
	bool isDead() const;
	//TODO: fix - more accurate hitbox
	RectF getHitbox() const;
	const VecF2& getPosConst() const;
protected:
	Entity(const VecF2& pos, int spriteState, const SpriteContainer&,const VecF2& vel = { 0.f,0.f }, float HP = 300.f,float speed = 0.f, float maxVel = 0.f);
	VecF2 pos;
	VecF2 vel;
	SpriteContainer sprites;
	float speed;
	float maxVel;
	int spriteState;
	float HP;
};