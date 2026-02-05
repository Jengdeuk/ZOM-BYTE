#include "Character.h"

Character::Character(const InitData& initData, const Status& status)
	: Super(initData),
	status(status)
{
}

void Character::Move(float deltaTime, const Vector2<float>& direction)
{
	SetPosition(GetPosition() + direction * status.moveSpeed * deltaTime);
}
