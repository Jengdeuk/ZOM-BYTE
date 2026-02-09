#pragma once

#include "Weapon.h"

class Barrel : public Weapon
{
	RTTI_DECLARATIONS(Barrel, Weapon)

public:
	Barrel(const Weapon::InitData& initData);

private:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

public:
	virtual void Fire(const int dirIdx) override;
};
