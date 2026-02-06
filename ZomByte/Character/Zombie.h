#pragma once

#include "Character/Character.h"

#include <vector>

using namespace JD;

class Weapon;

class Zombie : public Character
{
	RTTI_DECLARATIONS(Zombie, Character)

public:
	Zombie(const InitData& initData, const Status& status);

public:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

private:
	Weapon* currentWeapon = nullptr;
	std::vector<Weapon*> weapons;
};
