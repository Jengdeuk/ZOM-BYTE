#include "Pistol.h"

#include "Level/Level.h"
#include "Actor/Character/Player.h"
#include "Actor/Bullet/Bullet.h"

#include <memory>

Pistol::Pistol(const Weapon::InitData& initData)
	: Super(initData)
{
}

void Pistol::BeginPlay()
{
	Super::BeginPlay();
}

void Pistol::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void Pistol::Draw()
{
}

void Pistol::Fire(const int dirIdx)
{
	if (!Super::IsFireable())
	{
		return;
	}

	Super::Fire(dirIdx);

	Actor::InitData actorInitData;
	actorInitData.position = GetOwner()->GetPosition();
	actorInitData.color = Color::White;
	actorInitData.sortingOrder = 4;

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
