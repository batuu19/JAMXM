#include "Font.h"

const SpriteContainer Font::chars = SpriteContainer({ "sprites//font.bmp" }, 16, 6, 32, 32);

Surface Font::getChar(char c)
{
	{
		return chars.get(c - first);
	}
}


