#include "Shotgun.h"

#include "Level/Level.h"
#include "Character/Player.h"
#include "Bullet/Bullet.h"

#include <memory>

const int Shotgun::bulletDirIdx[8][3] =
{
	{ 3, 0, 1 },
	{ 0, 1, 2 },
	{ 1, 2, 4 },
	{ 0, 3, 5 },
	{ 2, 4, 7 },
	{ 3, 5, 6 },
	{ 5, 6, 7 },
	{ 6, 7, 4 }
};

Shotgun::Shotgun(const Weapon::InitData& initData)
	: Super(initData)
{
}

void Shotgun::BeginPlay()
{
	Super::BeginPlay();
}

void Shotgun::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void Shotgun::Draw()
{
}

void Shotgun::Fire(const int dirIdx)
{
	if (!Super::IsFireable())
	{
		return;
	}

	Actor::InitData actorInitData;
	actorInitData.position = Vector2<int>(GetOwner()->GetPosition());
	actorInitData.color = Color::White;
	actorInitData.sortingOrder = 6;

	Bullet::InitData initData;
	initData.damage = GetAttackRate();
	initData.lifeTime = 0.15f;
	initData.moveSpeed = 70.0f;

	for (int i = 0; i < 3; ++i)
	{
		const int idx = bulletDirIdx[dirIdx][i];
		initData.dirIdx = idx;
		initData.fireDir = Weapon::dir[idx];
		std::unique_ptr<Bullet> newBullet = std::make_unique<Bullet>(actorInitData, initData);
		GetLevel()->AddNewActor(std::move(newBullet));
	}

	Super::ReloadBullet();
}
