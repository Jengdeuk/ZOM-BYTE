#pragma once

#include "Weapon.h"

#include "Math/Vector2.h"

class Shotgun : public Weapon
{
	RTTI_DECLARATIONS(Shotgun, Weapon)

	static const int bulletDirIdx[8][3];

public:
	Shotgun(const Weapon::InitData& initData);

private:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

public:
	virtual void Fire(const int dirIdx) override;
};
