#pragma once

#include "Common/Common.h"

#include <Windows.h>

namespace JD
{
	class JD_API Vector2
	{
	public:
		Vector2();
		Vector2(int x, int y);
		~Vector2();

		operator COORD() const;

		Vector2& operator+=(const Vector2& other);
		Vector2& operator-=(const Vector2& other);

		friend bool operator==(const Vector2& left, const Vector2& right);

		static Vector2 Zero;
		static Vector2 One;
		static Vector2 Up;
		static Vector2 Right;

	public:
		int x = 0;
		int y = 0;
	};
}