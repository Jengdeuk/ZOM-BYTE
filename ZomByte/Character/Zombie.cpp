#include "Zombie.h"
#include "Player.h"
#include "Level/GameLevel.h"

#include "Core/Input.h"
#include "Game/Game.h"

#include "Physics/Collision.h"

#include "Weapon/Pistol.h"
#include "Weapon/Uzi.h"
#include "Weapon/Shotgun.h"

#include <memory>

using namespace JD;

Zombie::Zombie(const InitData& initData, const Status& status)
	: Super(initData, status)
{
	SetCollisionFilter(CollisionFilter{ ZOMBIE, PLAYER | ZOMBIE });
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
		SetImage("Z");
		break;
	case State::Bite:
		SetImage("X");
		timer.SetTargetTime(1.0f);
		break;
	case State::HitReact:
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

	Vector2<float> direction = target->GetPosition() - GetPosition();
	direction.Normalized();
	AccumulateMove(direction);
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

	if (GetHealthPoint() == 0)
	{
		(GetOwner()->As<GameLevel>())->OnKilled();
	}
}
