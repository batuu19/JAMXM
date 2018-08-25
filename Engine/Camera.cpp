#include "Camera.h"

void Camera::handleInput(Keyboard& kbd)
{
	if (kbd.KeyIsPressed('D'))
	{
		nextDir = RIGHT;
	}
	if (kbd.KeyIsPressed('A'))
	{
		nextDir = LEFT;
	}
	if (kbd.KeyIsPressed('S'))
	{
		nextDir = DOWN;
	}
	if (kbd.KeyIsPressed('W'))
	{
		nextDir = UP;
	}
}

void Camera::update(float dt)
{
	pos -= vectorsNormalized[nextDir] * dt * cameraMoveSpeed;
	nextDir = -1;
}
