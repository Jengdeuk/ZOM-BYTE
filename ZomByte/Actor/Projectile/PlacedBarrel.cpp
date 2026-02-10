#include "PlacedBarrel.h"

#include "Level/GameLevel.h"
#include "Physics/Collision.h"

#include "Actor/Effect/ExplosionEffect.h"
#include "Actor/Weapon/Weapon.h"

#include <cmath>

PlacedBarrel::PlacedBarrel(const Actor::InitData& actorInitData, const InitData& initData)
	: Super(actorInitData),
	damage(initData.damage),
	weaponDamage(initData.weaponDamage)
{
	timer.SetTargetTime(initData.lifeTime);
	SetCollisionFilter(CollisionFilter{ WALL, PLAYER | ZOMBIE | ITEM | WALL });
}

void PlacedBarrel::BeginPlay()
{
	Super::BeginPlay();

	timer.Reset();
}

void PlacedBarrel::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	timer.Tick(deltaTime);

	static const int targetTime = static_cast<int>(timer.GetTargetTime());
	sprintf_s(timeBuffer, "%d", targetTime - static_cast<int>(timer.GetElapsedTime()));
	SetImage(timeBuffer);
	if (timer.IsTimeOut())
	{
		Explosion();
		return;
	}
}

void PlacedBarrel::Explosion()
{
	Destroy();

	const Vector2<float> centerPos{ Vector2<int>(GetPosition()) };

	// ExplosionEffect
	Actor::InitData initData;
	initData.sortingOrder = 10;

	initData.position = centerPos;
	std::unique_ptr<ExplosionEffect> newEffect = std::make_unique<ExplosionEffect>(initData, damage, weaponDamage);
	GetOwner()->AddNewActor(std::move(newEffect));

	for (int j = 1; j <= 5; ++j)
	{
		for (int i = 0; i < 8; ++i)
		{
			initData.position = centerPos + Weapon::dir[i] * j;
			std::unique_ptr<ExplosionEffect> newEffect = std::make_unique<ExplosionEffect>(initData, damage, weaponDamage);
			GetOwner()->AddNewActor(std::move(newEffect));
		}
	}
}
