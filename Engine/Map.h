#pragma once

#include "Colors.h"
#include "Graphics.h"
#include "Config.h"
#include "Surface.h"
#include <assert.h>
#include "Camera.h"
#include <string>

//open maps during game not at beginning 

class Map
{
public:
	Map() = default;
	Map(const Map&) = delete;
	void draw(Graphics&, VecF2 cameraPos) const;
	const RectI& getRect() const;
private:
	class AI
	{
	public:
		AI(std::string filename);

		void draw(Graphics&, VecF2 cameraPos) const;
	private:
		int width;
		int branch;
		RectI bounds;
		std::vector<VecF2> points;
	};
private:
	AI mapAI = "sprites\\maps\\w0.ai";
	//Surface mapSprite = "sprites\\maps\\road_big_1500x1500.bmp";
	//Surface mapSprite = "sprites\\road_800x600.bmp";
	Surface mapSprite = "sprites\\maps\\w0.bmp";
	VecF2 pos = getZeroVec<float>();
};