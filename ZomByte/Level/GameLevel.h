#pragma once

#include "Level/Level.h"

#include "Math/Vector2.h"

using namespace JD;

class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel(const Vector2<int>& mapSize);

public:
	inline const Vector2<int>& GetMapSize() const { return mapSize; }

private:
	Vector2<int> mapSize;
};
