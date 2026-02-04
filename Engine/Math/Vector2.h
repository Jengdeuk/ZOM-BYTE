#pragma once

#include "Common/Common.h"

#include <Windows.h>

namespace JD
{
	template<typename T>
	class Vector2
	{
	public:
		Vector2() {}
		Vector2(T x, T y)
			: x(x), y(y)
		{
		}
		~Vector2() {}

		template<typename U>
		explicit Vector2(const Vector2<U>& other)
			: x(static_cast<T>(other.x)), y(static_cast<T>(other.y))
		{
		}

		operator COORD() const
		{
			return COORD{ static_cast<short>(x), static_cast<short>(y) };
		}

		Vector2& operator+=(const Vector2& other)
		{
			x += other.x;
			y += other.y;

			return *this;
		}
		Vector2& operator-=(const Vector2& other)
		{
			x -= other.x;
			y -= other.y;

			return *this;
		}

		friend bool operator==(const Vector2& left, const Vector2& right);

	public:
		T x = 0;
		T y = 0;
	};
}