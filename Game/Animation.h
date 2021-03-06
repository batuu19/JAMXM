#pragma once
#include "SpriteContainer.h"
#include "Graphics.h"
#include "Entity.h"

class Animation : public DynamicEntity, public StaticEntity
{
public:
	Animation(VecI2 pos, std::string filename, int frames, int frameWidth, int frameHeight, bool looping = false, float frameTime = 0.1f);
	Animation(VecI2 pos, std::string filename, int frames, bool looping = false, float frameTime = 0.1f);
	Animation(VecI2 pos, std::string filename, int frameWidth, int frameHeight, bool looping = false, float frameTime = 0.1f);
	Animation(const Animation&) = delete;
	Animation(Animation&&) = default;
	Animation& operator=(const Animation&) = default;

	void update(float dt) override;
	void draw(Graphics&, const VecF2& cameraPos) const override;
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