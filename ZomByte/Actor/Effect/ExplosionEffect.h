#pragma once

#include "Effect.h"

using namespace JD;

class ExplosionEffect : public Effect
{
	RTTI_DECLARATIONS(ExplosionEffect, Effect)

public:
	ExplosionEffect(const Actor::InitData& initData, const int damage, const int weaponDamage);

private:
	virtual void Tick(float deltaTime) override;

public:
	inline const int GetDamage() const { return damage; }
	inline const int GetWeaponInitDamage() const { return weaponDamage; }

private:
	int damage = 0;
	int weaponDamage = 0;
};
