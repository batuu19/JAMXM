#pragma once

#include "Colors.h"
#include "Graphics.h"
#include "Config.h"
#include "Surface.h"
#include <assert.h>
#include "Camera.h"
#include <string>
#include "MapHelper.h"

//open maps during game not at beginning 

class Map
{
public:
	Map(int mapNumber);
	Map(const Map&) = delete;
	void draw(Graphics&, VecF2 cameraPos) const;
	const RectI& getRect() const;

	Hitbox getHitbox() const;
private:
	class AI
	{
	public:
		AI(std::string filename);
		AI(int mapNumber);

		void draw(Graphics&, VecF2 cameraPos) const;
	private:
		int width;
		int branch;
		RectI bounds;
		std::vector<VecF2> points;
	};
private:
	AI mapAI;
	//Surface mapSprite = "sprites\\maps\\road_big_1500x1500.bmp";
	//Surface mapSprite = "sprites\\road_800x600.bmp";
	Surface mapSprite;
	VecF2 pos = getZeroVec<float>();
	Hitbox hitbox;
};