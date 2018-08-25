#pragma once

#include "Colors.h"
#include "Graphics.h"
#include "Config.h"
#include "Surface.h"
#include <assert.h>

//open maps during game not at beginning 

class Map
{
public:
	Map() = default;
	void draw(Graphics&) const;
private:
	Surface mapSprite = "sprites\\road_800x600.bmp";
	;}
;