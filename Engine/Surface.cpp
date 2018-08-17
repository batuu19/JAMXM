#include "Surface.h"
#include "ChiliWin.h"
#include <assert.h>
#include <fstream>

Surface::Surface(const std::string & filename)
{
	std::ifstream file(filename, std::ios::binary);

	BITMAPFILEHEADER bmFileHeader;
	file.read(reinterpret_cast<char*>(&bmFileHeader), sizeof(bmFileHeader));

	BITMAPINFOHEADER bmInfoHeader;
	file.read(reinterpret_cast<char*>(&bmInfoHeader), sizeof(bmInfoHeader));

	assert(bmInfoHeader.biBitCount == 24);
	assert(bmInfoHeader.biCompression == BI_RGB);

	width = bmInfoHeader.biWidth;
	height = bmInfoHeader.biHeight;

	pPixels = new Color[width*height];

	file.seekg(bmFileHeader.bfOffBits);
	const int padding = (4 - (width * 3) % 4) % 4;

	for (int y = height - 1; y >= 0;y--)
	{
		for (int x = 0; x < width; x++)
		{
			putPixel(x, y, Color(file.get(), file.get(), file.get()));
		}
		file.seekg(padding, std::ios::cur);
	}
}

Surface::Surface(int width, int height)
	:
	width(width),
	height(height),
	pPixels( new Color[width*height])
{
}

Surface::Surface(int width, int height, Color * pPixels)
	:
	width(width),
	height(height),
	pPixels(new Color[width*height])
{
	for (int i = 0; i < width*height; i++)
	{
		this->pPixels[i] = pPixels[i];
	}
}

Surface::Surface(const Surface & rhs)
	:
	Surface(rhs.width, rhs.height)
{
	const int nPixels = width*height;
	for (int i = 0; i < nPixels; i++)
	{
		pPixels[i] = rhs.pPixels[i];
	}
}

Surface::~Surface()
{
	delete[] pPixels;
	pPixels = nullptr;
}

Surface & Surface::operator=(const Surface & rhs)
{
	width = rhs.width;
	height = rhs.height;

	delete[] pPixels;
	pPixels = new Color[width * height];

	const int nPixels = width*height;
	for (int i = 0; i < nPixels; i++)
	{
		pPixels[i] = rhs.pPixels[i];
	}
	return *this;
}

void Surface::putPixel(int x, int y, Color c)
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);
	pPixels[y * width + x] = c;
}

void Surface::putPixel(int i, Color c)
{
	assert(i < width * height);
	pPixels[i] = c;
}

Color Surface::getPixel(int x, int y) const
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);
	return pPixels[y * width + x];
}

Color Surface::getPixel(int i) const
{
	assert(i < width * height);
	return pPixels[i];
}

int Surface::getWidth() const
{
	return width;
}

int Surface::getHeight() const
{
	return height;
}

RectI Surface::getRect() const
{
	return{ 0,width,0,height };
}

Surface Surface::rotateVertically() const
{
	int nPixels = width * height;
	Color* newPPixels = new Color[nPixels];

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			newPPixels[(height - y - 1)*width + x] = pPixels[y*width + x];
		}
	}

	Surface surf(width,height, newPPixels);
	delete newPPixels;
	return surf;
}

Surface Surface::rotateHorizontally() const
{
	int nPixels = width * height;
	Color* newPPixels = new Color[nPixels];

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			newPPixels[y*width + (width - x - 1)] = pPixels[y*width + x];
		}
	}

	Surface surf(width, height, newPPixels);
	delete newPPixels;
	return surf;
}

Surface Surface::rotateVertAndHor() const
{
	int nPixels = width * height;
	Color* newPPixels = new Color[nPixels];

	for (int i = 0; i < nPixels; i++)
	{
		newPPixels[nPixels - i - 1] = pPixels[i];
	}

	Surface surf(width, height, newPPixels);
	delete newPPixels;
	return surf;
}

Surface Surface::getPart(const RectI & srcRect) const
{
	int width = srcRect.getWidth();
	int height = srcRect.getHeight();
	Surface surf(width, height);

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			surf.pPixels[y*width + x] = pPixels[(y + srcRect.top)* this->width + (x + srcRect.left)];
		}
	}

	return surf;
}
