#include "Animation.h"

Animation::Animation(VecI2 pos,std::string filename, int frames, int frameWidth, int frameHeight,bool looping, float frameTime)
	:
	pos(pos),
	sprites({ filename }, frames, 1, frameWidth, frameHeight, false),
	frameTimer(frameTime),
	allFrames(frames),
	looping(looping)
{
}

Animation::Animation(VecI2 pos, std::string filename, int frames, bool looping, float frameTime)
	:
	pos(pos),
	sprites({ filename }, frames, 1,false),
	frameTimer(frameTime),
	allFrames(frames),
	looping(looping)

{
}

Animation::Animation(VecI2 pos, std::string filename, int frameWidth, int frameHeight, bool looping, float frameTime)
	:
	pos(pos),
	sprites({ filename },(unsigned int)frameWidth, (unsigned int)frameHeight, false),
	frameTimer(frameTime),
	allFrames(sprites.getSize()),
	looping(looping)
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
				if(!looping)
				endOfAnimation = true;
			}
		}
	}
	
}

void Animation::draw(Graphics & gfx, VecF2 cameraPos) const
{
	if (!endOfAnimation)
	{
		gfx.drawSprite(pos - cameraPos, sprites[activeFrame]);
	}
}

void Animation::stop()
{
	endOfAnimation = true;
}

bool Animation::isEnded() const
{
	return endOfAnimation;
}
