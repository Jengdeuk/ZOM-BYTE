#include "Pistol.h"

#include "Level/Level.h"
#include "Character/Player.h"
#include "Bullet/Bullet.h"

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

	Bullet::InitData initData;
	initData.dirIdx = dirIdx;
	initData.lifeTime = 1.5f;
	initData.moveSpeed = 20.0f;
	initData.firePos = GetOwner()->GetPosition();
	initData.fireDir = Weapon::dir[dirIdx];

	std::unique_ptr<Bullet> newBullet = std::make_unique<Bullet>(initData);
	GetLevel()->AddNewActor(std::move(newBullet));

	Super::ReloadBullet();
}
