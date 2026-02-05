#pragma once

#include "Character/Character.h"

#include <vector>

using namespace JD;

class Weapon;

class Player : public Character
{
	RTTI_DECLARATIONS(Player, Character)
	
public:
	Player(const InitData& initData, const Status& status);

public:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

private:
	void MovementInput(float deltaTime);
	void ChangeWeaponInput();
	void UseWeaponInput();

private:
	Weapon* currentWeapon = nullptr;
	std::vector<Weapon*> weapons;
};
