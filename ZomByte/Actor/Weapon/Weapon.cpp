#include "Weapon.h"

#include "Actor/Character/Player.h"

const Vector2<float> Weapon::dir[8] =
{
	Vector2<float>(-1.0f, 1.0f).Normalized(),
	Vector2<float>(0.0f, 1.0f).Normalized(),
	Vector2<float>(1.0f, 1.0f).Normalized(),
	Vector2<float>(-1.0f, 0.0f).Normalized(),
	Vector2<float>(1.0f, 0.0f).Normalized(),
	Vector2<float>(-1.0f, -1.0f).Normalized(),
	Vector2<float>(0.0f, -1.0f).Normalized(),
	Vector2<float>(1.0f, -1.0f).Normalized()
};

Weapon::Weapon(const InitData& initData)
	: Super(Super::InitData()),
	attackRate(initData.attackRate),
	initAR(initData.attackRate),
	magazine(initData.magazine),
	clip(initData.clip),
	owner(initData.owner)
{
	timer.SetTargetTime(initData.reloadTime);
}

void Weapon::BeginPlay()
{
	Super::BeginPlay();

	timer.Reset();
}

void Weapon::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	timer.Tick(deltaTime);
}

void Weapon::Draw()
{
}

bool Weapon::IsFireable()
{
	return (timer.IsTimeOut() && magazine >= clip);
}

void Weapon::ReloadBullet()
{
	timer.Reset();
}

void Weapon::RefillAmmo(const int amount)
{
	magazine += amount * clip;
}

void Weapon::Fire(const int dirIdx)
{
	magazine -= clip;
}

Level* Weapon::GetLevel() const
{
	return owner->GetOwner();
}

void Weapon::SetAttackRate(const int ownerAR)
{
	attackRate = initAR * ownerAR;
}
