#pragma once

#include "Colors.h"
#include "Graphics.h"
#include "Config.h"
#include "Surface.h"
#include <assert.h>
#include "Camera.h"
#include <string>
#include "MapHelper.h"
#include "Hitbox.h"

//open maps during game not at beginning 

static constexpr char DEBUG_MAP_SPRITE[] = "Sprites\\maps\\trasa.bmp";

class Map : public StaticEntity
{
public:
	Map(int mapNumber);
	Map(const Map&) = delete;
	void draw(Graphics&, const VecF2& cameraPos) const override;
	const RectI& getRect() const;
	const VecI2 getCarStartPos() const;
	const int getCarStartDirection() const;
private:
	//AI mapAI;
	//Surface mapSprite = "sprites\\maps\\road_big_1500x1500.bmp";
	//Surface mapSprite = "sprites\\road_800x600.bmp";
	Surface mapSprite;
	VecF2 pos = { 0.f,0.f };
};