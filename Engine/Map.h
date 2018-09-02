#pragma once

#include "Colors.h"
#include "Graphics.h"
#include "Config.h"
#include "Surface.h"
#include <assert.h>
#include "Camera.h"

//open maps during game not at beginning 

class Map
{
public:
	Map() = default;
	Map(const Map&) = delete;
	void draw(Graphics&) const;
	void draw(Graphics&, VecF2 cameraPos) const;
	const RectI& getRect() const;
private:
	Surface mapSprite = "sprites\\road_big_1500x1500.bmp";
	//Surface mapSprite = "sprites\\road_800x600.bmp";
	VecF2 pos = getZeroVec<float>();
};