#pragma once

#include "Colors.h"
#include <string>
#include "Rect.h"
#include <vector>

//pPixels[y*width + x];
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
	void putPixel(int i, Color c);
	Color getPixel(int x, int y) const;
	Color getPixel(int i) const;
	int getWidth() const;
	int getHeight() const;
	RectI getRect() const;

	Surface rotateVertically() const;
	Surface rotateHorizontally() const;
	Surface rotateVertAndHor() const;
	Surface getPart(const RectI& srcRect) const;

	std::vector<VecI2>& getHitablePoints(Color chroma = Colors::Magenta) const;
private:
	Color* pPixels = nullptr;
	int width;
	int height;
};