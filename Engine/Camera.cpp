#include "Camera.h"

void Camera::handleInput(Keyboard& kbd)
{
	if (kbd.KeyIsPressed('D'))
	{
		nextDir = vectorsNormalized[RIGHT];
	}
	if (kbd.KeyIsPressed('A'))
	{
		nextDir = vectorsNormalized[LEFT];
	}
	if (kbd.KeyIsPressed('S'))
	{
		nextDir = vectorsNormalized[DOWN];
	}
	if (kbd.KeyIsPressed('W'))
	{
		nextDir = vectorsNormalized[UP];
	}
}

void Camera::move(int dir)
{
	nextDir = vectorsNormalized[dir];
}

void Camera::move(const VecF2& dir)
{
	nextDir = dir;
}

void Camera::update(float dt)
{
	if (nextDir != VecF2(0.f, 0.f))
	{
		pos += nextDir * dt * cameraMoveSpeed;
		nextDir = { 0.f,0.f };
	}
	
}
