#include "Animation.h"

Animation::Animation(VecI2 pos,std::string filename, int frames, int frameWidth, int frameHeight, float frameTime)
	:
	pos(pos),
	sprites({ filename }, frames, 1, frameWidth, frameHeight, false),
	frameTimer(frameTime),
	allFrames(frames)
{
}

void Animation::update(float dt)
{
	if (!endOfAnimation)
	{
		time += dt;
		if (time > frameTimer)
		{
			time = 0.f;
			activeFrame++;
			if (activeFrame >= allFrames)
			{
				activeFrame = 0;
				endOfAnimation = true;
			}
		}
	}
	
}

void Animation::draw(Graphics & gfx) const
{
	if (!endOfAnimation)
	{
		gfx.drawSprite(pos, sprites[activeFrame]);
	}
}

bool Animation::isEnded() const
{
	return endOfAnimation;
}
