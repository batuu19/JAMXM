#pragma once

#include "Graphics.h"
#include "Directions.h"
#include <math.h>

class Car
{

public:
	Car(int startX, int startY, Color c);

	void turnLeft();
	void turnRight();
	void update();
	void speedup(bool faster = true);
	void draw(Graphics& gfx) const;
private:
	float velocity = 0.0f;
	float speed = 0.4f;;//speedup rate
	float xPos, yPos;
	static constexpr int width = 25;
	static constexpr int height = 25;
	int dir = RIGHT;
	Color c;


};