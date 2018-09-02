#pragma once
#include "BMath.h"
#include "Rect.h"
#include "Keyboard.h"
#include "Directions.h"

class Camera
{
public:
	Camera() = default;
	Camera(const Camera&) = delete;
	void handleInput(Keyboard&);
	void move(int dir);
	void move(const VecF2& dir);
	void centerOn(const VecF2& point,const RectI& screenRect);
	template<typename T>
	void centerOn(const T& object, const RectI& screenRect);
	void update(float dt);
	VecF2 pos = getZeroVec<float>();
private:
	float cameraMoveSpeed = 270.f;
	VecF2 nextDir = { 0.f,0.f };
};

template<typename T>
inline void Camera::centerOn(const T & object, const RectI & screenRect)
{
	centerOn(object.getPosConst(), screenRect);
}
