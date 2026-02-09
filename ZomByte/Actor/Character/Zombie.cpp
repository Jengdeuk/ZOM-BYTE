#include "Zombie.h"
#include "Player.h"
#include "Level/GameLevel.h"

#include "Core/Input.h"
#include "Game/Game.h"

#include "Physics/Collision.h"

#include "Actor/Weapon/Pistol.h"
#include "Actor/Weapon/Uzi.h"
#include "Actor/Weapon/Shotgun.h"

#include <memory>

using namespace JD;

Zombie::Zombie(const InitData& initData, const Status& status)
	: Super(initData, status)
{
	SetCollisionFilter(CollisionFilter{ ZOMBIE, PLAYER | ZOMBIE | ITEM });
}

void Zombie::BeginPlay()
{
	Super::BeginPlay();

	currentState = State::Chase;
	target = (GetOwner()->As<GameLevel>())->GetPlayer();
}

void Zombie::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	switch (currentState)
	{
	case State::Chase:
		TickChase(deltaTime);
		break;
	case State::Bite:
		TickBite(deltaTime);
		break;
	case State::HitReact:
		TickHitReact(deltaTime);
		break;
	default:
		break;
	}
}

void Zombie::Draw()
{
	Super::Draw();
}

void Zombie::ChangeState(const State newState)
{
	timer.Reset();
	switch (newState)
	{
	case State::Chase:
		currentState = State::Chase;
		SetImage("Z");
		break;
	case State::Bite:
		currentState = State::Bite;
		SetImage("O");
		timer.SetTargetTime(0.5f);
		break;
	case State::HitReact:
		currentState = State::HitReact;
		SetImage("Z");
		timer.SetTargetTime(0.5f);
		break;
	default:
		break;
	}
}

void Zombie::TickChase(float deltaTime)
{
	if (!target)
	{
		return;
	}

	Vector2<float> dv = target->GetPosition() - GetPosition();

	float distance = sqrt(dv.x * dv.x + dv.y * dv.y);
	if (distance <= 1.0f)
	{
		target->OnDamaged(GetStatus().attackRate);
		if (target->IsDead())
		{
			target->SetImage("#");
		}

		const Vector2<float> knockBackDir{ (target->GetPosition() - GetPosition()).Normalized() };
		target->AccumulateForce(knockBackDir * 15.0f);

		ChangeState(State::Bite);
		return;
	}

	AccumulateMove(dv.Normalized());
}

void Zombie::TickBite(float deltaTime)
{
	timer.Tick(deltaTime);
	if (timer.IsTimeOut())
	{
		ChangeState(State::Chase);
	}
}

void Zombie::TickHitReact(float deltaTime)
{
	timer.Tick(deltaTime);
	if (timer.IsTimeOut())
	{
		ChangeState(State::Chase);
	}
}

void Zombie::OnDamaged(const int damage)
{
	Super::OnDamaged(damage);

	ChangeState(State::HitReact);

	if (GetStatus().healthPoint == 0)
	{
		(GetOwner()->As<GameLevel>())->OnKilled();
	}
}
