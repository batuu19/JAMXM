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
	Map(Graphics&);
	Map(const Config&,Graphics&);
	void draw();
private:
	Surface mapSprite;
	//width and height same as window
	Graphics& gfx;
};