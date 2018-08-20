#pragma once
#include <math.h>
#include <algorithm>

template<typename T>
T sq(T x){	return x*x;}

class Vec2;
class Vei2;
///Vector Float


class Vec2
{
public:
	Vec2() = default;
	Vec2(float x_in, float y_in);
	Vec2(int x_in, int y_in);
	Vec2 operator+(const Vec2& rhs) const;
	Vec2 operator+(const float rhs) const;
	Vec2& operator+=(const Vec2& rhs);
	Vec2& operator+=(const float rhs);
	float operator*(const Vec2& rhs) const;//dot product
	Vec2 operator*(float rhs) const;
	Vec2& operator*=(float rhs);
	Vec2 operator-(const Vec2& rhs) const;
	Vec2 operator-(const float rhs) const;
	Vec2& operator-=(const Vec2& rhs);
	Vec2& operator-=(const float rhs);
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

const Vec2 zeroVec{ 0.0f,0.0f };
///Vector Int

class Vei2
{
public:
	Vei2() = default;
	Vei2(int x_in, int y_in);
	Vei2 operator+(const Vei2& rhs) const;
	Vei2& operator+=(const Vei2& rhs);
	Vei2 operator*(int rhs) const;
	Vei2& operator*=(int rhs);
	Vei2 operator-(const Vei2& rhs) const;
	Vei2& operator-=(const Vei2& rhs);
	Vei2 operator/(int rhs) const;
	Vei2& operator/=(int rhs);
	float GetLength() const;
	int GetLengthSq() const;
	explicit operator Vec2();
public:
	int x;
	int y;
};