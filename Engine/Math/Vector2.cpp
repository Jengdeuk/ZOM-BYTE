#include "Vector2.h"

namespace JD
{
	template<typename T>
	Vector2<T> operator+(Vector2<T> left, const Vector2<T>& right)
	{
		return left += right;
	}

	template<typename T>
	Vector2<T> operator-(Vector2<T> left, const Vector2<T>& right)
	{
		return left -= right;
	}

	template<typename T>
	bool operator==(const Vector2<T>& left, const Vector2<T>& right)
	{
		return left.x == right.x && left.y == right.y;
	}

	template<typename T>
	bool operator!=(const Vector2<T>& left, const Vector2<T>& right)
	{
		return !(left == right);
	}
}