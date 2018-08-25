#pragma once
#include "BMath.h"
#include "Keyboard.h"
#include "Directions.h"

class Camera
{
public:
	Camera() = default;
	void handleInput(Keyboard&);
	void move(int dir);
	void move(const VecF2& dir);
	void update(float dt);
	VecF2 pos = getZeroVec<float>();
private:
	float cameraMoveSpeed = 270.f;
	VecF2 nextDir = { 0.f,0.f };
};