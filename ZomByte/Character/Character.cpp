#include "Character.h"

Character::Character(const InitData& initData, const Status& status)
	: Super(initData),
	status(status)
{
}

void Character::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	velocity = Vector2<float>();
}

void Character::TransformUpdate(float deltaTime)
{
	SetPosition(GetPosition() + velocity * deltaTime);
}

void Character::AccumulateForce(const Vector2<float>& velocity)
{
	this->velocity += velocity;
}

void Character::AccumulateMove(const Vector2<float>& direction)
{
	velocity += direction * status.moveSpeed;
}
