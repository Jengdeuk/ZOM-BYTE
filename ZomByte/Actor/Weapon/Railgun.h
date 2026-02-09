#pragma once

#include "Weapon.h"

class Railgun : public Weapon
{
	RTTI_DECLARATIONS(Railgun, Weapon)

public:
	Railgun(const Weapon::InitData& initData);

private:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

public:
	virtual void Fire(const int dirIdx) override;
};
