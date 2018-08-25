#pragma once
#include "SpriteContainer.h"
#include "Graphics.h"

class Animation
{
public:
	Animation(VecI2 pos,std::string filename,int frames, int frameWidth,int frameHeight,bool looping = false,float frameTime = 0.1f);
	void update(float dt);
	void draw(Graphics&) const;
	void stop();

	bool isEnded() const;
private:
	SpriteContainer sprites;
	float frameTimer;
	float time = 0.f;
	VecI2 pos = { 0,0 };
	int activeFrame = 0;
	int allFrames;

	bool endOfAnimation = false;
	bool looping;

};