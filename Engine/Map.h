#pragma once

#include "Colors.h"
#include "Graphics.h"
#include "Config.h"
#include <fstream>
#include <assert.h>

//open maps during game not at beginning 

class Map
{
public:
	Map(Graphics&);
	Map(const Config&,Graphics&);
	Map(const Map&);
	Map& operator=(const Map&) = delete;
	~Map();
	void draw();
private:
	Color* pPixels = nullptr;
	//width and height same as window
	Graphics& gfx;
	void putPixel(int x, int y, Color c);
};