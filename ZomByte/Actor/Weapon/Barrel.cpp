#include "Barrel.h"

#include "Level/Level.h"
#include "Actor/Character/Player.h"
#include "Actor/Projectile/PlacedBarrel.h"

#include <memory>

Barrel::Barrel(const Weapon::InitData& initData)
	: Super(initData)
{
}

void Barrel::BeginPlay()
{
	Super::BeginPlay();
}

void Barrel::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void Barrel::Draw()
{
}

void Barrel::Fire(const int dirIdx)
{
	if (!Super::IsFireable())
	{
		return;
	}

	Super::Fire(dirIdx);

	Actor::InitData actorInitData;
	actorInitData.image = "B";
	actorInitData.position = GetOwner()->GetPosition() + Weapon::dir[dirIdx];
	actorInitData.color = Color::DarkMagenta;
	actorInitData.sortingOrder = 9;

	PlacedBarrel::InitData initData;
	initData.damage = GetAttackRate();
	initData.weaponDamage = GetInitAR();
	initData.lifeTime = 5.0f;

	std::unique_ptr<PlacedBarrel> newBarrel = std::make_unique<PlacedBarrel>(actorInitData, initData);
	GetLevel()->AddNewActor(std::move(newBarrel));

	Super::ReloadBullet();
}
