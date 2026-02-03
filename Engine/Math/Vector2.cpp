#include "Vector2.h"

namespace JD
{
	Vector2 Vector2::Zero(0, 0);
	Vector2 Vector2::One(1, 1);
	Vector2 Vector2::Up(0, 1);
	Vector2 Vector2::Right(1, 0);

	Vector2::Vector2()
	{
	}

	Vector2::Vector2(int x, int y)
		: x(x), y(y)
	{
	}

	Vector2::~Vector2()
	{
	}

	Vector2::operator COORD() const
	{
		return COORD{ static_cast<short>(x), static_cast<short>(y) };
	}

	Vector2& Vector2::operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	Vector2& Vector2::operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}

	Vector2 operator+(Vector2 left, const Vector2& right)
	{
		return left += right;
	}

	Vector2 operator-(Vector2 left, const Vector2& right)
	{
		return left -= right;
	}

	bool operator==(const Vector2& left, const Vector2& right)
	{
		return (left.x == right.x) && (left.y == right.y);
	}

	bool operator!=(const Vector2& left, const Vector2& right)
	{
		return !(left == right);
	}
}