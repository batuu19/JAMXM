#pragma once

#include "Graphics.h"
#include "BMath.h"
#include <vector>
#include "Surface.h"
#include "Directions.h"
#include "SpriteContainer.h"
#include "Hitbox.h"
#include <stdexcept>

//for car and rocket
//TODO: what about explosion and other?
class Entity
{
public:
	friend class UI;
public:
	virtual ~Entity() = default;

	virtual void update(float dt);
	virtual void draw(Graphics&, const VecF2& cameraPos) const;
	virtual void reset();

	bool damage(float amount);//return true if destroyed
	void kill();
	bool isDead() const;
	//TODO: fix - more accurate hitbox
	const Hitbox& getHitbox() const;
	const VecF2& getPosConst() const;
protected:
	Entity(const VecF2& pos, int spriteState, const SpriteContainer&,
		const VecF2& vel = { 0.f,0.f }, float HP = 300.f, float speed = 0.f, float maxVel = 0.f,
		float invincibilityTime = 0.f, bool invincibleAtStart = false
	);
	VecF2 pos;
	VecF2 vel;
	SpriteContainer sprites;
	float speed;
	float maxVel;
	int spriteState;
	float HP;
	float maxHP;
	bool invincible;
	float invincibleTime = 0.f;
	float invincibleTimer;

	Hitbox hitbox;
};