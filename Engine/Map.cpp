#include "Map.h"



Map::Map(Graphics & gfx)
	:
	gfx(gfx),
	pPixels(new Color[gfx.ScreenWidth * gfx.ScreenHeight])
{
}

Map::Map(const Config & config, Graphics & gfx)
	:
	gfx(gfx)
{
	std::string filename = config.getMapFilename();
	std::ifstream file(filename, std::ios::binary); BITMAPFILEHEADER bmFileHeader;
	file.read(reinterpret_cast<char*>(&bmFileHeader), sizeof(bmFileHeader));

	BITMAPINFOHEADER bmInfoHeader;
	file.read(reinterpret_cast<char*>(&bmInfoHeader), sizeof(bmInfoHeader));

	assert(bmInfoHeader.biBitCount == 24);
	assert(bmInfoHeader.biCompression == BI_RGB);
	assert(bmInfoHeader.biWidth == gfx.ScreenWidth);
	assert(bmInfoHeader.biHeight == gfx.ScreenHeight);

	pPixels = new Color[gfx.ScreenWidth * gfx.ScreenHeight];

	file.seekg(bmFileHeader.bfOffBits);
	const int padding = (4 - (gfx.ScreenWidth * 3) % 4) % 4;

	for (int y = gfx.ScreenHeight - 1; y >= 0; y--)
	{
		for (int x = 0; x < gfx.ScreenWidth; x++)
		{
			putPixel(x, y, Color(file.get(), file.get(), file.get()));
		}
		file.seekg(padding, std::ios::cur);
	}
}

Map::Map(const Map & rhs)
	:
	Map(rhs.gfx)
{
	const int nPixels = gfx.ScreenWidth * gfx.ScreenHeight;
	for (int i = 0; i < nPixels; i++)
	{
		pPixels[i] = rhs.pPixels[i];
	}
}

Map::~Map()
{
	delete pPixels;
	pPixels = nullptr;
}

void Map::draw()
{
	for (int y = 0; y < gfx.ScreenHeight; y++)
	{
		for (int x = 0; x < gfx.ScreenWidth; x++)
		{
			gfx.putPixel(x, y, pPixels[y* gfx.ScreenWidth + x]);
		}
	}
}

void Map::putPixel(int x, int y, Color c)
{
	assert(x >= 0);
	assert(x < int(Graphics::ScreenWidth));
	assert(y >= 0);
	assert(y < int(Graphics::ScreenHeight));
	pPixels[y* gfx.ScreenWidth + x] = c;
}
