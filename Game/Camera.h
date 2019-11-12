#pragma once
#include "BMath.h"
#include "Rect.h"
#include "Keyboard.h"
#include "Directions.h"

class Camera
{
public:
	Camera() = default;
	Camera(const VecF2& startPos);
	Camera(const Camera&) = delete;
	void handleInput(Keyboard::Event);
	void move(int dir);
	void move(const VecF2& dir);
	void centerOn(const VecF2& point,const RectI& screenRect);
	template<typename T>
	void centerOn(const T& object, const RectI& screenRect);
	void update(float dt);
	void reset();
	VecF2 pos = { 0.f,0.f };
private:
	float cameraMoveSpeed = 270.f;
	VecF2 nextDir = { 0.f,0.f };
};

template<typename T>
inline void Camera::centerOn(const T & object, const RectI & screenRect)
{
	centerOn(object.getPosConst(), screenRect);
}
