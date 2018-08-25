#pragma once
#include "BMath.h"
#include "Keyboard.h"
#include "Directions.h"

class Camera
{
public:
	Camera() = default;
	void handleInput(Keyboard&);
	void update(float dt);
	VecF2 pos = getZeroVec<float>();
	int nextDir = -1;//-1 -> no direction
private:
	float cameraMoveSpeed = 200.f;
};