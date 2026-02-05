#include "Character.h"

Character::Character(const InitData& initData, const Status& status)
	: Super(initData),
	status(status)
{
}

void Character::Move(const Vector2<float>& direction)
{
	SetPosition(GetPosition() + direction * status.moveSpeed);
}
