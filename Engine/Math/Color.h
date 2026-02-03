#pragma once

#include "Common/Common.h"

#include <Windows.h>

namespace JD
{
	enum class JD_API Color : unsigned short
	{
		Black = 0,
		Red = FOREGROUND_RED,
		Green = FOREGROUND_GREEN,
		Blue = FOREGROUND_BLUE,
		White = Red | Green | Blue
	};
}