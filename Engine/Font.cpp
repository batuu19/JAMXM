#include "Font.h"

const SpriteContainer Font::chars = SpriteContainer({ "sprites//font.bmp" }, 16, 6, characterSize, characterSize);

Surface Font::getChar(char c)
{
	{
		return chars.get(c - first);
	}
}

void Font::write(Graphics& gfx, VecI2 pos, std::string text, bool alignLeft)
{

	if (alignLeft)
	{
		auto iter = text.begin();
		while (iter < text.end())
		{
			gfx.drawSprite(pos, getChar(*iter));
			pos.x += characterSize;
			iter++;
		}
	}
	else
	{
		pos.x -= characterSize;
		auto iter = text.rbegin();
		while (iter < text.rend())
		{
			gfx.drawSprite(pos, getChar(*iter));
			pos.x -= characterSize;
			iter++;
		}
	}

}


