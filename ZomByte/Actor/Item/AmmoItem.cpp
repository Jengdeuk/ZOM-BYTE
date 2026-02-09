#include "AmmoItem.h"

#include "Actor/Character/Player.h"

static const Actor::InitData ammoItemInitData[] =
{
	{ "p", Vector2<float>(), Color::White, 9 },
	{ "u", Vector2<float>(), Color::Yellow, 9 },
	{ "s", Vector2<float>(), Color::White, 9 },
	{ "b", Vector2<float>(), Color::Magenta, 9 },
	{ "r", Vector2<float>(), Color::Cyan, 9 }
};

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
	case WeaponType::Uzi:
	case WeaponType::Shotgun:
	case WeaponType::Barrel:
	case WeaponType::Railgun:
		(target->As<Player>())->RefillAmmo(static_cast<int>(data.type), data.amount);
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
	case WeaponType::Uzi:
	case WeaponType::Shotgun:
	case WeaponType::Barrel:
	case WeaponType::Railgun:
		rv = ammoItemInitData[static_cast<int>(type)];
		break;
	default:
		break;
	}

	rv.position = pos;

	return rv;
}
