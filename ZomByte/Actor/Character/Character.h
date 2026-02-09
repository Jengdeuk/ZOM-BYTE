#pragma once

#include "Actor/Actor.h"
#include "Util/Timer.h"

using namespace JD;

class Character : public Actor
{
	RTTI_DECLARATIONS(Character, Actor)

	struct Status
	{
		int healthPoint = 0;
		int attackRate = 0;
		float moveSpeed = 0.0f;
	};

public:
	Character(const InitData& initData, const Status& status);

public:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

public:
	virtual void OnDamaged(const int damage);
	void DrinkPotion(const int amount);
	virtual void StrengthTraining(const int amount);
	void SpeedTraining(const int amount);

public:
	virtual void TransformUpdate(float deltaTime) override;

public:
	void AccumulateForce(const Vector2<float>& velocity);
	void AccumulateMove(const Vector2<float>& direction);

public:
	inline const Status& GetStatus() const { return status; }
	inline const bool IsDead() const { return isDead; }

private:
	void PlayDamagedAnimation();

private:
	Status status;
	Vector2<float> moveVelocity;
	Vector2<float> forceVelocity;

private:
	bool isPlayingDamagedAnimation = false;
	Timer damagedAnimationTimer;

private:
	bool isDead = false;
	Timer destroyTimer;
};
