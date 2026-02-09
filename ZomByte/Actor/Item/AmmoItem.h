#pragma once

#include "Item.h"

class AmmoItem : public Item
{
	RTTI_DECLARATIONS(AmmoItem, Item)

	enum class WeaponType
	{
		Pistol,
		Uzi,
		Shotgun,
		Barrel,
		Railgun,
		Count
	};

	struct InitData
	{
		WeaponType type = WeaponType::Count;
		int amount = 0;
		Vector2<float> spawnPos;
	};

public:
	AmmoItem(InitData initData);

private:
	virtual void ApplyEffect(Character* target) override;

private:
	const Actor::InitData& GetActorInitData(const WeaponType type, Vector2<float>& pos);

private:
	InitData data;
};
