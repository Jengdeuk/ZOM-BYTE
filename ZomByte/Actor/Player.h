#pragma once

#include "Actor/Actor.h"

using namespace JD;

class Player : public Actor
{
	RTTI_DECLARATIONS(Player, Actor)
	
public:
	Player(const Vector2<int>& position);

public:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;
};