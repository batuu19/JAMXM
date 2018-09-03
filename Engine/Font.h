#pragma once
#include "SpriteContainer.h"
class Font
{
public:
	static Surface getChar(char c);
private:
	static const char first = ' ';
	static const char last = '~';
	static const SpriteContainer chars //= SpriteContainer({ "sprites//font.bmp" }, 16, 6, 32, 32)
		;
};
