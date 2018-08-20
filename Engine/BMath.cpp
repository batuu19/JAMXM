#include "BMath.h"

///VEC2
Vec2::Vec2(float x_in, float y_in)
	:
	x(x_in),
	y(y_in)
{
}

Vec2::Vec2(int x_in, int y_in)
	:
	x((float)x_in),
	y((float)y_in)
{
}

Vec2 Vec2::operator+(const Vec2& rhs) const
{
	return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator+(const float rhs) const
{
	return Vec2(x + rhs, y + rhs);
}

Vec2& Vec2::operator+=(const Vec2& rhs)
{
	return *this = *this + rhs;
}

Vec2 & Vec2::operator+=(const float rhs)
{
	return *this = *this + rhs;
}

float Vec2::operator*(const Vec2 & rhs) const
{
	return x * rhs.x + y * rhs.y;
}

Vec2 Vec2::operator*(float rhs) const
{
	return Vec2(x * rhs, y * rhs);
}

Vec2& Vec2::operator*=(float rhs)
{
	return *this = *this * rhs;
}

Vec2 Vec2::operator-(const Vec2& rhs) const
{
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator-(const float rhs) const
{
	return Vec2(x - rhs, y - rhs);
}

Vec2& Vec2::operator-=(const Vec2& rhs)
{
	return *this = *this - rhs;
}

Vec2 & Vec2::operator-=(const float rhs)
{
	return *this = *this - rhs;
}

float Vec2::getLength() const
{
	return std::sqrt(getLengthSq());
}

float Vec2::getLengthSq() const
{
	return x * x + y * y;
}

Vec2& Vec2::normalize()
{
	return *this = getNormalized();
}

Vec2 Vec2::getNormalized() const
{
	const float len = getLength();
	if (len != 0.0f)
	{
		return *this * (1.0f / len);
	}
	return *this;
}

Vec2::operator Vei2() const
{
	return{ (int)x,(int)y };
}

///VEI2

Vei2::Vei2(int x_in, int y_in)
	:
	x(x_in),
	y(y_in)
{
}

Vei2 Vei2::operator+(const Vei2& rhs) const
{
	return Vei2(x + rhs.x, y + rhs.y);
}

Vei2& Vei2::operator+=(const Vei2& rhs)
{
	return *this = *this + rhs;
}

Vei2 Vei2::operator*(int rhs) const
{
	return Vei2(x * rhs, y * rhs);
}

Vei2& Vei2::operator*=(int rhs)
{
	return *this = *this * rhs;
}

Vei2 Vei2::operator-(const Vei2& rhs) const
{
	return Vei2(x - rhs.x, y - rhs.y);
}

Vei2& Vei2::operator-=(const Vei2& rhs)
{
	return *this = *this - rhs;
}

Vei2 Vei2::operator/(int rhs) const
{
	return Vei2(x / rhs, y / rhs);
}

Vei2& Vei2::operator/=(int rhs)
{
	return *this = *this / rhs;
}

float Vei2::GetLength() const
{
	return std::sqrt(float(GetLengthSq()));
}

int Vei2::GetLengthSq() const
{
	return x * x + y * y;
}

Vei2::operator Vec2()
{
	return{ (float)x,(float)y };
}