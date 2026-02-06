#include "Zombie.h"
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
	SetCollisionFilter(CollisionFilter{ ZOMBIE, PLAYER });
}

void Zombie::BeginPlay()
{
	Super::BeginPlay();
}

void Zombie::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void Zombie::Draw()
{
	Super::Draw();
}

void Zombie::OnDamaged(const int damage)
{
	Super::OnDamaged(damage);

	if (GetHealthPoint() == 0)
	{
		(GetOwner()->As<GameLevel>())->OnKilled();
	}
}
