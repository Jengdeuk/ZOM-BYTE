#pragma once

#include "Actor/Actor.h"

class Player : public JD::Actor
{
	RTTI_DECLARATIONS(Player, Actor)
	
public:
	Player(const JD::Vector2& position);

public:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;
};