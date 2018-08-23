#include "Animation.h"

Animation::Animation(std::string filename, int frames, int frameWidth, int frameHeight, float frameTime)
	:
	sprites({ filename }, frames, 1, frameWidth, frameHeight, false),
	frameTimer(frameTime),
	allFrames(frames)
{
}

void Animation::play(VecI2 pos)
{
	active = true;
	this->pos = pos;
}

void Animation::update(float dt)
{
	if (active)
	{
		time += dt;
		if (time > frameTimer)
		{
			time = 0.f;
			activeFrame++;
			if (activeFrame >= allFrames)
			{
				activeFrame = 0;
				active = false;
			}
		}
	}
	
}

void Animation::draw(Graphics & gfx) const
{
	if (active)
	{
		gfx.drawSprite(pos, sprites[activeFrame]);
	}
}
