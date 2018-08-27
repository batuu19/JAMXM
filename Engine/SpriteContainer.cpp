#include "SpriteContainer.h"

SpriteContainer::SpriteContainer(const Surface& surf, int rows, int lines,
					int width, int height, bool rotateAtCreate)
	:
	rows(rows),
	lines(lines),
	height(height),
	width(width)
{
	const int framesCount = rows * lines;
	RectI* frames = new RectI[framesCount];

	int left, right, up, down;
	left = 0;
	right = width;
	up = 0;
	down = height;

	//making frames
	for (int y = 0; y < lines; y++)
	{
		for (int x = 0; x < rows; x++)
		{
			frames[y*rows + x] = { left,right,up,down };
			left += width;
			right += width;
		}
		down += height;
		up += height;
		left = 0;
		right = width;
	}
	//for example car
	if (rotateAtCreate && rows == 5 && lines == 1)
	{
		sprites.emplace_back(surf.getPart(frames[0]));//UP

		sprites.emplace_back(surf.getPart(frames[1]));
		sprites.emplace_back(surf.getPart(frames[2]));//UP_RIGHT
		sprites.emplace_back(surf.getPart(frames[3]));
		sprites.emplace_back(surf.getPart(frames[4]));//RIGHT

		sprites.emplace_back(surf.getPart(frames[3]).rotateVertically());
		sprites.emplace_back(surf.getPart(frames[2]).rotateVertically());//DOWN_RIGHT
		sprites.emplace_back(surf.getPart(frames[1]).rotateVertically());
		sprites.emplace_back(surf.getPart(frames[0]).rotateVertically());//DOWN

		sprites.emplace_back(surf.getPart(frames[1]).rotateVertAndHor());
		sprites.emplace_back(surf.getPart(frames[2]).rotateVertAndHor());//DOWN_LEFT
		sprites.emplace_back(surf.getPart(frames[3]).rotateVertAndHor());

		sprites.emplace_back(surf.getPart(frames[4]).rotateHorizontally());//LEFT
		sprites.emplace_back(surf.getPart(frames[3]).rotateHorizontally());
		sprites.emplace_back(surf.getPart(frames[2]).rotateHorizontally());//UP_LEFT
		sprites.emplace_back(surf.getPart(frames[1]).rotateHorizontally());

		sprites.shrink_to_fit();
	}

	//for example explosion
	else
	{
		for (int i = 0; i < framesCount; i++)
		{
			sprites.push_back(surf.getPart(frames[i]));
		}
	}
	delete[] frames;
}

Surface & SpriteContainer::operator[](int i)
{
	return sprites[i];
}

const Surface & SpriteContainer::operator[](int i) const
{
	return sprites[i];
}

Surface SpriteContainer::get(int i) const
{
	return sprites[i];
}

Surface SpriteContainer::get(int row, int line) const
{
	return sprites[line * rows + row];
}

size_t SpriteContainer::getSize() const
{
	return sprites.size();
}
