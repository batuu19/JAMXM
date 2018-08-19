#pragma once
#include "Surface.h"
#include <vector>

class SpriteContainer
{
public:
	//make without copying surface
	SpriteContainer(const Surface& allCars, int rows, int lines,int height,int width, bool rotateAtCreate = true);

	//for sure operator[]?
	Surface& operator[](int i);
	const Surface& operator[](int i) const;
	Surface get(int i) const;
	Surface get(int row, int line) const;

	size_t getSize() const;
private:
	int rows;
	int lines;
	int height;
	int width;
	std::vector<Surface> sprites;
};