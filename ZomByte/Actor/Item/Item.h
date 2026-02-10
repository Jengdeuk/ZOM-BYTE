#pragma once

#include "Actor/Actor.h"
#include "Util/Timer.h"

using namespace JD;

class Character;

class Item : public Actor
{
	RTTI_DECLARATIONS(Item, Actor)

public:
	Item(Actor::InitData initData);

private:
	virtual void Tick(float deltaTime) override;

public:
	virtual void ApplyEffect(Character* target) = 0;

private:
	Timer timer;
};
