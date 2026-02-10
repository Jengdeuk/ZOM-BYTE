#include "Uzi.h"

#include "Level/Level.h"
#include "Actor/Character/Player.h"
#include "Actor/Projectile/Bullet.h"

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

	Super::Fire(dirIdx);

	Actor::InitData actorInitData;
	actorInitData.position = GetOwner()->GetPosition();
	actorInitData.color = Color::Yellow;
	actorInitData.sortingOrder = 5;

	Bullet::InitData initData;
	initData.damage = GetAttackRate();
	initData.weaponDamage = GetInitAR();
	initData.dirIdx = dirIdx;
	initData.lifeTime = 0.5f;
	initData.moveSpeed = 100.0f;
	initData.drag = 1.0f;
	initData.fireDir = Weapon::dir[dirIdx];

	std::unique_ptr<Bullet> newBullet = std::make_unique<Bullet>(actorInitData, initData);
	GetLevel()->AddNewActor(std::move(newBullet));

	Super::ReloadBullet();
}
