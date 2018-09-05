#pragma once
#include "Surface.h"
#include <vector>

class SpriteContainer
{
public:
	SpriteContainer(const Surface& surf, int rows, int lines,int width, int height, bool rotateAtCreate = true);
	SpriteContainer(const Surface& surf, int rows, int lines, bool rotateAtCreate = true);
	SpriteContainer(const Surface& surf, unsigned int width, unsigned int height, bool rotateAtCreate = true);

	Surface& operator[](int i);
	const Surface& operator[](int i) const;
	Surface get(int i) const;
	Surface get(int row, int line) const;


	size_t getSize() const;
	int getWidth() const;
	int getHeight() const;
	RectI getRect() const;
private:
	int rows;
	int lines;
	int height;
	int width;
	std::vector<Surface> sprites;
};