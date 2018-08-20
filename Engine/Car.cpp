#include "Car.h"

Car::Car(const Config& config)
	:
	pos(config.getCarStartXPos(), config.getCarStartYPos()),
	speed(config.getCarSpeed()),
	maxVel(config.getCarMaxVelocity()),
	dir(config.getCarStartDir()),
	turnRate(config.getCarTurnRate()),
	config(config),
	sprites(config.getCarImageFileName(),5,1,70,70)
{
	vel = { 0.0f,0.0f };
}

void Car::turnLeft()
{
	const float dt = turnTimer.mark();
	if (leftTurn >= turnRate)
	{
		dir = (dir - turnValue + DIRECTIONS_COUNT) % DIRECTIONS_COUNT;
		leftTurn = 0.f;
	}
	leftTurn += dt;

	vel = vectorsNormalized[dir] * (vel * vectorsNormalized[dir]);
}

void Car::turnRight()
{
	const float dt = turnTimer.mark();

	if (rightTurn >= turnRate)
	{
		dir = (dir + turnValue) % DIRECTIONS_COUNT;
		rightTurn = 0.f;
	}
	rightTurn += dt;

	vel = vectorsNormalized[dir] * (vel * vectorsNormalized[dir]);
}

void Car::update()
{	
	for (auto &r : rocketsFired)
	{
		r.update();
	}
	pos += vel;
}

void Car::speedup(bool faster)
{
	float speedFactor = faster ? speed : -speed;
	const float actualVelSq = vel.getLengthSq();
	//TODO: that's bad, can't stop when max or 0 vel
	if(actualVelSq < maxVel * maxVel && actualVelSq >= 0)
		vel += vectorsNormalized[dir] * speedFactor;


}

void Car::draw(Graphics & gfx) const
{
	drawCar(gfx);
	for (auto r : rocketsFired)
	{
		r.draw(gfx);
	}
}

void Car::reset()
{
	pos.x = (float)config.getCarStartXPos();
	pos.y = (float)config.getCarStartYPos();
	dir = config.getCarStartDir();
	vel = { 0.0f,0.0f };

	rocketsFired.clear();
}

void Car::shoot()
{
	const float dt = shootTimer.mark();
	if (lastShot >= shootRate)
	{
		rocketsFired.emplace_back(config, pos, dir);
		lastShot = 0.f;
	}
	
	lastShot += dt;
}

std::string Car::getDebugInfo() const
{
	std::stringstream ss;

	ss  << "x=" << pos.x << " y=" << pos.y 
	    << " velX=" << vel.x << " velY=" << vel.y 
		<< " maxVel=" << maxVel;

	return ss.str();
}

void Car::drawCar(Graphics & gfx) const
{
	gfx.drawSprite((VecI2)pos, sprites[dir]);
}

/*

template<typename T>
inline Rect<T>::Rect(T left_in, T right_in, T top_in, T bottom_in)
:
left(left_in),
right(right_in),
top(top_in),
bottom(bottom_in)
{
}

template<typename T>
inline Rect<T>::Rect(const Vec2 & topLeft, const Vec2 & bottomRight)
:
Rect(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y)
{
}

template<typename T>
inline Rect<T>::Rect(const Vec2 & topLeft, T width, T height)
:
Rect(topLeft, topLeft + Vec2(width, height))
{
}

template<typename T>
inline bool Rect<T>::IsOverlappingWith(const Rect & other) const
{
return right > other.left && left < other.right
&& bottom > other.top && top < other.bottom;
}

template<typename T>
inline bool Rect<T>::IsContainedBy(const Rect & other) const
{
return left >= other.left && right <= other.right &&
top >= other.top && bottom <= other.bottom;
}

template<typename T>
inline Rect Rect<T>::FromCenter(const Vec2 & center, T halfWidth, T halfHeight)
{
const Vec2 half(halfWidth, halfHeight);
return Rect(center - half, center + half);
}

template<typename T>
inline Rect Rect<T>::GetExpanded(T offset) const
{
return Rect(left - offset, right + offset, top - offset, bottom + offset);
}

template<typename T>
inline Vec2 Rect<T>::GetCenter() const
{
return Vec2((left + right) / (T)2, (top + bottom) / (T)2);
}

template<typename T>
inline T Rect<T>::getWidth() const
{
return right - left;
}

template<typename T>
inline T Rect<T>::getHeight() const
{
return down - up;
}
*/