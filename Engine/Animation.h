#pragma once
#include "SpriteContainer.h"
#include "Graphics.h"

class Animation
{
public:
	Animation(std::string filename,int frames, int frameWidth,int frameHeight,float frameTime = 0.1f);
	void play(VecI2 pos);
	void update(float dt);
	void draw(Graphics&) const;
private:
	SpriteContainer sprites;
	float frameTimer;
	float time = 0.f;
	bool active = false;
	VecI2 pos = { 0,0 };
	int activeFrame = 0;
	int allFrames;

};