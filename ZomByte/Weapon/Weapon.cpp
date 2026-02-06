#include "Weapon.h"

#include "Character/Player.h"

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
	owner(initData.owner)
{
	timer.SetTargetTime(initData.timerTime);
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
	return timer.IsTimeOut();
}

void Weapon::ReloadBullet()
{
	timer.Reset();
}

Level* Weapon::GetLevel() const
{
	return owner->GetOwner();
}
