#include "AmmoItem.h"

#include "Actor/Character/Player.h"

static const Actor::InitData paItemInitData{ "p", Vector2<float>(), Color::White, 9 };
static const Actor::InitData uaItemInitData{ "u", Vector2<float>(), Color::Yellow, 9 };
static const Actor::InitData saItemInitData{ "s", Vector2<float>(), Color::White, 9 };

AmmoItem::AmmoItem(InitData initData)
	: Super(GetActorInitData(initData.type, initData.spawnPos)),
	data(initData)
{
}

void AmmoItem::ApplyEffect(Character* target)
{
	switch (data.type)
	{
	case WeaponType::Pistol:
		(target->As<Player>())->RefillAmmo(0, data.amount);
		break;
	case WeaponType::Uzi:
		(target->As<Player>())->RefillAmmo(1, data.amount);
		break;
	case WeaponType::Shotgun:
		(target->As<Player>())->RefillAmmo(2, data.amount);
		break;
	default:
		break;
	}

	Destroy();
}

const Actor::InitData& AmmoItem::GetActorInitData(const WeaponType type, Vector2<float>& pos)
{
	Actor::InitData rv;
	switch (type)
	{
	case WeaponType::Pistol:
		rv = paItemInitData;
		break;
	case WeaponType::Uzi:
		rv = uaItemInitData;
		break;
	case WeaponType::Shotgun:
		rv = saItemInitData;
		break;
	default:
		break;
	}

	rv.position = pos;

	return rv;
}
