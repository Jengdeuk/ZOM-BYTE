#pragma once

#include "Actor/Actor.h"

using namespace JD;

class Weapon : public Actor
{
	RTTI_DECLARATIONS(Weapon, Actor)

public:
	Weapon();

private:
	virtual void Draw() override;
};
