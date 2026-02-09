#include "Railgun.h"

#include "Level/Level.h"
#include "Actor/Character/Player.h"
#include "Actor/Effect/Railslug.h"

#include <memory>

Railgun::Railgun(const Weapon::InitData& initData)
	: Super(initData)
{
}

void Railgun::BeginPlay()
{
	Super::BeginPlay();
}

void Railgun::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void Railgun::Draw()
{
}

void Railgun::Fire(const int dirIdx)
{
	if (!Super::IsFireable())
	{
		return;
	}

	Super::Fire(dirIdx);

	Railslug::InitData initData;
	initData.damage = GetAttackRate();
	initData.weaponDamage = GetInitAR();
	initData.dirIdx = dirIdx;
	initData.lifeTime = 0.42f;

	Actor::InitData actorInitData;
	actorInitData.sortingOrder = 11;

	const Vector2<float> startPos{ Vector2<int>(GetOwner()->GetPosition()) };
	for (int i = 1; i <= 60; ++i)
	{
		actorInitData.position = startPos + Weapon::dir[dirIdx] * static_cast<float>(i);
		std::unique_ptr<Railslug> newRailslug = std::make_unique<Railslug>(actorInitData, initData);
		GetLevel()->AddNewActor(std::move(newRailslug));
	}

	Super::ReloadBullet();
}
