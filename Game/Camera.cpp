#include "Camera.h"

Camera::Camera(const VecF2 & startPos)
	:
	pos(startPos)
{
}

void Camera::move(int dir)
{
	nextDir = vectorsNormalized[dir];
}

void Camera::move(const VecF2& dir)
{
	nextDir = dir;
}

void Camera::centerOn(const VecF2 & point, const RectI& screenRect)
{
	pos = { point.x - screenRect.getWidth() / 2,point.y - screenRect.getHeight() / 2 };
}

void Camera::update(float dt)
{
	if (nextDir != VecF2(0.f, 0.f))
	{
		pos += nextDir * dt * cameraMoveSpeed;
		nextDir = { 0.f,0.f };
	}
	
}

void Camera::reset()
{
	pos = { 0.f,0.f };
}
