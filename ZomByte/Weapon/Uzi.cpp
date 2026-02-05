#include "Uzi.h"

#include "Level/Level.h"
#include "Character/Player.h"
#include "Bullet/Bullet.h"

#include <memory>

Uzi::Uzi(const Weapon::InitData& initData)
	: Super(initData)
{
}

void Uzi::BeginPlay()
{
	Super::BeginPlay();
}

void Uzi::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void Uzi::Draw()
{
}

void Uzi::Fire(const int dirIdx)
{
	if (!Super::IsFireable())
	{
		return;
	}

	Actor::InitData actorInitData;
	actorInitData.position = Vector2<int>(GetOwner()->GetPosition());
	actorInitData.color = Color::Yellow;
	actorInitData.sortingOrder = 5;

	Bullet::InitData initData;
	initData.damage = GetAttackRate();
	initData.dirIdx = dirIdx;
	initData.lifeTime = 1.5f;
	initData.moveSpeed = 40.0f;
	initData.fireDir = Weapon::dir[dirIdx];

	std::unique_ptr<Bullet> newBullet = std::make_unique<Bullet>(actorInitData, initData);
	GetLevel()->AddNewActor(std::move(newBullet));

	Super::ReloadBullet();
}
