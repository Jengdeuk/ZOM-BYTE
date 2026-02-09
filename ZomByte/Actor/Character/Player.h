#pragma once

#include "Actor/Character/Character.h"

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

private:
	void TakeWeapons();
	void EnhanceWeapons();

private:
	virtual void StrengthTraining(const int amount) override;

private:
	void MovementInput(float deltaTime);
	void ChangeWeaponInput();
	void UseWeaponInput();

private:
	virtual void TransformUpdate(float deltaTime) override;

private:
	Weapon* currentWeapon = nullptr;
	std::vector<Weapon*> weapons;
};
