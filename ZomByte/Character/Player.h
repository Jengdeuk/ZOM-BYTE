#pragma once

#include "Character/Character.h"

using namespace JD;

class Player : public Character
{
	RTTI_DECLARATIONS(Player, Character)
	
public:
	Player(const InitData& initData, const Status& status);

public:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;
};
