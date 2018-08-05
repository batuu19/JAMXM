#pragma once

#include "Graphics.h"
#include "Directions.h"

class Car
{

public:
	Car(int startX, int startY, Color c);

	void update(Direction newDir);
	void update();
	void draw(Graphics& gfx) const;
private:
	float velocity;
	int xPos, yPos;
	static constexpr int width = 100;
	static constexpr int height = 25;
	Direction dir;
	Color c;


};