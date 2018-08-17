#pragma once

#include "Colors.h"
#include <string>
#include "RectI.h"

class Surface
{
public:
	Surface(const std::string& filename);
	Surface(int width, int height);
	Surface(int width, int height, Color* pPixels);
	Surface(const Surface&);
	~Surface();
	Surface& operator=(const Surface&);
	void putPixel(int x, int y, Color c);
	Color getPixel(int x, int y) const;
	int getWidth() const;
	int getHeight() const;
	RectI getRect() const;

	Surface rotateVertically() const;
	Surface rotateHorizontally() const;
	Surface rotateVertAndHor() const;
private:
	Color* pPixels = nullptr;
	int width;
	int height;
};