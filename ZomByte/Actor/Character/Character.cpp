#include "Character.h"

#include "Level/Level.h"
#include "Actor/Effect/BloodEffect.h"

#include <cmath>

Character::Character(const InitData& initData, const Status& status)
	: Super(initData),
	status(status)
{
	damagedAnimationTimer.SetTargetTime(0.3f);
	destroyTimer.SetTargetTime(0.5f);
}

void Character::BeginPlay()
{
	Super::BeginPlay();

	damagedAnimationTimer.Reset();
	destroyTimer.Reset();
}

void Character::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	moveVelocity = Vector2<float>();
	forceVelocity = forceVelocity * std::exp(-8.0f * deltaTime);

	if (isDead)
	{
		destroyTimer.Tick(deltaTime);
		if (destroyTimer.IsTimeOut())
		{
			Destroy();

			// BloodEffect
			Actor::InitData initData;
			initData.position = Vector2<int>(GetPosition());
			initData.sortingOrder = 1;
			std::unique_ptr<BloodEffect> newEffect = std::make_unique<BloodEffect>(initData);
			GetOwner()->AddNewActor(std::move(newEffect));
		}

		return;
	}

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
		isDead = true;
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
