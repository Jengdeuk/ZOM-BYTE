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
		float timerTime = 0.0f;
		int attackRate = 0;
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
	virtual void Fire(const int dirIdx) = 0;

public:
	inline Player* GetOwner() const { return owner; }
	Level* GetLevel() const;

private:
	Timer timer;
	int attackRate = 0;

private:
	Player* owner = nullptr;
};
