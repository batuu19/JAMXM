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
	Entity(VecF2 pos,
		std::string spriteFileName, int spriteWidth, int spriteHeight, int spritesRows = 5, int spritesLines = 1);
	Entity(VecF2 pos,int dir,
		std::string spriteFileName, int spriteWidth, int spriteHeight, int spritesRows = 5, int spritesLines = 1);
	Entity(const Entity&) = delete;

	void update(float dt);
	void draw(Graphics&) const;
	void draw(Graphics&, VecF2 cameraPos) const;
	void reset();

	void damage(float amount);
	bool isDead() const;
	//TODO: fix - more accurate hitbox
	RectF getHitbox() const;
protected:
	VecF2 pos;
	const SpriteContainer sprites;
	int dir;
	float HP = 300.f;
	bool dead = false;

	int width;
	int height;
};