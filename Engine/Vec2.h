#pragma once
#include <cmath>
#include "Vei2.h"
//Make Vei and Vec in the same file?
class Vec2
{
public:
	Vec2() = default;
	Vec2(float x_in, float y_in);
	Vec2(int x_in, int y_in);
	Vec2 operator+(const Vec2& rhs) const;
	Vec2& operator+=(const Vec2& rhs);
	Vec2 operator*(float rhs) const;
	Vec2& operator*=(float rhs);
	Vec2 operator-(const Vec2& rhs) const;
	Vec2& operator-=(const Vec2& rhs);
	float getLength() const;
	float getLengthSq() const;
	Vec2& normalize();
	Vec2 getNormalized() const;
	explicit operator Vei2() const;
public:
	float x;
	float y;

public:
};

//const Vec2 zeroVec{ 0.0f,0.0f };