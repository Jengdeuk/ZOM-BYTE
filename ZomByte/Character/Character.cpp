#include "Character.h"

#include <cmath>

Character::Character(const InitData& initData, const Status& status)
	: Super(initData),
	status(status)
{
	damagedAnimationTimer.SetTargetTime(0.3f);
}

void Character::BeginPlay()
{
	Super::BeginPlay();

	damagedAnimationTimer.Reset();
}

void Character::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	moveVelocity = Vector2<float>();
	forceVelocity = forceVelocity * std::exp(-8.0f * deltaTime);

	if (!isPlayingDamagedAnimation)
	{
		return;
	}

	damagedAnimationTimer.Tick(deltaTime);
	if (damagedAnimationTimer.IsTimeOut())
	{
		isPlayingDamagedAnimation = false;
		SetColor(Super::GetInitData().color);
	}
}

void Character::OnDamaged(const int damage)
{
	status.healthPoint -= damage;
	if (status.healthPoint <= 0)
	{
		status.healthPoint = 0;
		Destroy();
	}

	PlayDamagedAnimation();
}

void Character::TransformUpdate(float deltaTime)
{
	const Vector2<float> velocity = moveVelocity + forceVelocity;
	SetPosition(GetPosition() + velocity * deltaTime);
}

void Character::AccumulateForce(const Vector2<float>& velocity)
{
	forceVelocity += velocity;
}

void Character::AccumulateMove(const Vector2<float>& direction)
{
	moveVelocity += direction * status.moveSpeed;
}

void Character::PlayDamagedAnimation()
{
	isPlayingDamagedAnimation = true;
	damagedAnimationTimer.Reset();
	SetColor(Color::DarkRed);
}
