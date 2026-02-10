#pragma once

#include "Actor/Actor.h"

#include "Util/Timer.h"

using namespace JD;

class PlacedBarrel : public Actor
{
	RTTI_DECLARATIONS(PlacedBarrel, Actor)

	struct InitData
	{
		int damage = 0;
		int weaponDamage = 0;
		float lifeTime = 0.0f;
	};

	static const char* PlacedBarrelImage[8];

public:
	PlacedBarrel(const Actor::InitData& actorInitData, const InitData& initData);

private:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

public:
	void Explosion();

public:
	inline const int GetDamage() const { return damage; }
	inline const int GetWeaponInitDamage() const { return weaponDamage; }

private:
	char timeBuffer[256] = {};
	int damage = 0;
	int weaponDamage = 0;
	Timer timer;
};
