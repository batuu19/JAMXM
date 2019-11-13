#pragma once
#include "Keyboard.h"

class PlayableEntity
{
public:
	virtual void handleInput(Keyboard::Event) = 0;
	virtual ~PlayableEntity() = default;
};
