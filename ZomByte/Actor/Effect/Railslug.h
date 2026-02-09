#pragma once

#include "Actor/Effect/Effect.h"
#include "Util/Timer.h"

using namespace JD;

class Railslug : public Effect
{
	RTTI_DECLARATIONS(Railslug, Effect)

	struct InitData
	{
		int damage = 0;
		int weaponDamage = 0;
		int dirIdx = 0;
		float lifeTime = 0.0f;
	};

	static const char* RailslugImage[8];

public:
	Railslug(const Actor::InitData& actorInitData, const InitData& initData);

private:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

public:
	inline const int GetDamage() const { return damage; }
	inline const int GetWeaponInitDamage() const { return weaponDamage; }

private:
	int damage = 0;
	int weaponDamage = 0;
	Timer timer;
};
