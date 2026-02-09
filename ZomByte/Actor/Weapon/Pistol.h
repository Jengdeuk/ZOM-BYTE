#pragma once

#include "Weapon.h"

class Pistol : public Weapon
{
	RTTI_DECLARATIONS(Pistol, Weapon)

public:
	Pistol(const Weapon::InitData& initData);

private:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

public:
	virtual void Fire(const int dirIdx) override;
};
