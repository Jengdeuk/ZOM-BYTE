#include "StatusItem.h"

#include "Actor/Character/Character.h"

static const Actor::InitData hpItemInitData{ "*", Vector2<float>(), Color::Red, 9 };
static const Actor::InitData arItemInitData{ "*", Vector2<float>(), Color::Yellow, 9 };
static const Actor::InitData msItemInitData{ "*", Vector2<float>(), Color::Cyan, 9 };

StatusItem::StatusItem(InitData initData)
	: Super(GetActorInitData(initData.status, initData.spawnPos)),
	data(initData)
{
}

void StatusItem::ApplyEffect(Character* target)
{
	switch (data.status)
	{
	case Status::HealthPoint:
		target->DrinkPotion(data.amount);
		break;
	case Status::AttackRate:
		target->StrengthTraining(data.amount);
		break;
	case Status::MoveSpeed:
		target->SpeedTraining(data.amount);
		break;
	default:
		break;
	}

	Destroy();
}

const Actor::InitData& StatusItem::GetActorInitData(const Status type, Vector2<float>& pos)
{
	Actor::InitData rv;
	switch (type)
	{
	case Status::HealthPoint:
		rv = hpItemInitData;
		break;
	case Status::AttackRate:
		rv = arItemInitData;
		break;
	case Status::MoveSpeed:
		rv = msItemInitData;
		break;
	default:
		break;
	}

	rv.position = pos;

	return rv;
}
