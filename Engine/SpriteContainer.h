#pragma once
#include "Surface.h"
#include <vector>
#include <iterator>

typedef std::vector<Surface>::iterator iterator;
typedef std::vector<Surface>::const_iterator const_iterator;

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
public:
	//iterator begin();
	//iterator end();
	const_iterator begin() const;
	const_iterator end() const;
};
