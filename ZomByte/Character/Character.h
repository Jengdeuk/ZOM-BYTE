#pragma once

#include "Actor/Actor.h"

using namespace JD;

class Character : public Actor
{
	RTTI_DECLARATIONS(Character, Actor)

	struct Status
	{
		int healthPoint = 0;
		int attackRate = 0;
		float moveSpeed = 0.0f;
	};

public:
	Character(const InitData& initData, const Status& status);

public:
	void Move(const Vector2<float>& direction);

private:
	Status status;
};
