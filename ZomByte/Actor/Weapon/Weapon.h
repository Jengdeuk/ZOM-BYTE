#pragma once

#include "Actor/Actor.h"

#include "Util/Timer.h"

using namespace JD;

class Player;

class Weapon : public Actor
{
	RTTI_DECLARATIONS(Weapon, Actor)

	struct InitData
	{
		float reloadTime = 0.0f;
		int attackRate = 0;
		int magazine = 0;
		int clip = 0;
		Player* owner = nullptr;
	};

	static const Vector2<float> dir[8];

public:
	Weapon(const InitData& initData);

public:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

public:
	bool IsFireable();
	void ReloadBullet();
	void RefillAmmo(const int amount);
	virtual void Fire(const int dirIdx);

public:
	inline Player* GetOwner() const { return owner; }
	Level* GetLevel() const;
	inline const int GetAttackRate() const { return attackRate; }
	void SetAttackRate(const int ownerAR);
	inline const int GetInitAR() const { return initAR; }
	inline const int GetMagazine() const { return magazine; }

private:
	Timer timer;
	int attackRate = 0;
	int initAR = 0;
	int magazine = 0;
	int clip = 0;

private:
	Player* owner = nullptr;
};
