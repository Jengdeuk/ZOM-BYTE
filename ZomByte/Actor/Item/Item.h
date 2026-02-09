#pragma once

#include "Actor/Actor.h"

using namespace JD;

class Character;

class Item : public Actor
{
	RTTI_DECLARATIONS(Item, Actor)

public:
	Item(Actor::InitData initData);

public:
	virtual void ApplyEffect(Character* target) = 0;
};
