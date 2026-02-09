#pragma once

#include "Actor/Character/Character.h"
#include "Util/Timer.h"

using namespace JD;

class Zombie : public Character
{
	RTTI_DECLARATIONS(Zombie, Character)

	enum class State
	{
		Chase,
		Bite,
		HitReact,
		Count
	};

public:
	Zombie(const InitData& initData, const Status& status);

public:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

public:
	void ChangeState(const State newState);

private:
	void TickChase(float deltaTime);
	void TickBite(float deltaTime);
	void TickHitReact(float deltaTime);

public:
	virtual void OnDamaged(const int damage) override;

private:
	State currentState = State::Chase;
	Character* target = nullptr;
	Timer timer;
};
