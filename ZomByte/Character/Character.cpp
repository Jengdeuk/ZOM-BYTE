#include "Character.h"

#include <cmath>

Character::Character(const InitData& initData, const Status& status)
	: Super(initData),
	status(status)
{
}

void Character::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	moveVelocity = Vector2<float>();
	forceVelocity = forceVelocity * std::exp(-8.0f * deltaTime);
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
