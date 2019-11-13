#pragma once
#include "BMath.h"
#include "Player.h"
#include "Entity.h"
#include "Map.h"
#include "Animation.h"
#include "BUtils.h"
#include "ContainerUtils.h"
#include "PhysicsUtils.h"
#include "Camera.h"
#include "UFO.h"
#include <exception>
#include "Font.h"

//TODO cache?
//use it for choosing levels
//move resposibility to Level
class World
{
public:
	World(const RectI& screenRect);
	World(const World&) = delete;
	World& operator=(const World&) = delete;
	void handleInput(Keyboard::Event);
	void update(float dt);
	void draw(Graphics&) const;
private:
	RectI screenRect;
	bool musicPlaying = true;
	Font font;


	//sounds
	Sound bgm = Sound(L"sound\\music\\music.wav", Sound::LoopType::AutoFullSound);
};