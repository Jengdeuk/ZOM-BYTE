#pragma once

#include "Weapon.h"

class Uzi : public Weapon
{
	RTTI_DECLARATIONS(Uzi, Weapon)

public:
	Uzi(const Weapon::InitData& initData);

private:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

public:
	virtual void Fire(const int dirIdx) override;
};
