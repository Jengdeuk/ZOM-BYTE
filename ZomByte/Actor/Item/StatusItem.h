#pragma once

#include "Item.h"

class StatusItem : public Item
{
	RTTI_DECLARATIONS(StatusItem, Item)

	enum class Status
	{
		HealthPoint,
		AttackRate,
		MoveSpeed,
		Count
	};

	struct InitData
	{
		Status status = Status::Count;
		int amount = 0;
		Vector2<float> spawnPos;
	};

public:
	StatusItem(InitData initData);

private:
	virtual void ApplyEffect(Character* target) override;

private:
	const Actor::InitData& GetActorInitData(const Status type, Vector2<float>& pos);

private:
	InitData data;
};
