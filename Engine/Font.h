#pragma once
#include "SpriteContainer.h"
#include "Graphics.h"
class Font
{
public:
	static Surface getChar(char c);
	static void write(Graphics&, VecI2 pos, std::string text, bool alignLeft = true);
	//maybe TODO
	//template<typename T>
	//static void write(Graphics&, VecI2 pos, T value, bool alignLeft = true);
private:
	static const char first = ' ';
	static const char last = '~';
	static const int characterSize = 32;
	static const SpriteContainer chars //= SpriteContainer({ "sprites//font.bmp" }, 16, 6, 32, 32)
		;
};
