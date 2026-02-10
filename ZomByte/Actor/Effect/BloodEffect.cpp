#include "BloodEffect.h"

#include "Util/Util.h"

#include "Level/GameLevel.h"
#include "Actor/Character/Player.h"
#include "Actor/Item/StatusItem.h"
#include "Actor/Item/AmmoItem.h"

static const Effect::EffectFrame effectSequence[] =
{
	{ "#", 0.15f, Color::Red },
	{ "#", 0.15f, Color::DarkRed }
};

BloodEffect::BloodEffect(const Actor::InitData& initData)
	: Super(initData)
{
	Effect::Init(effectSequence, sizeof(effectSequence) / sizeof(effectSequence[0]));
}

void BloodEffect::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (DestroyRequested())
	{
		SpawnItem();
	}
}

void BloodEffect::SpawnItem()
{
	float rv = Util::Randomf(0.0f, 1.0f);
	if (rv < 0.35f)
	{
		// StatusItem
		StatusItem::InitData initData;
		initData.spawnPos = GetPosition();

		float rvStat = Util::Randomf(0.0f, 1.0f);
		if (rvStat < 0.68f)
		{
			initData.status = StatusItem::Status::HealthPoint;
			initData.amount = 1;
		}
		else if (rvStat < 0.7f)
		{
			initData.status = StatusItem::Status::AttackRate;
			initData.amount = 1;
		}
		else
		{
			initData.status = StatusItem::Status::MoveSpeed;
			initData.amount = 1;
		}

		std::unique_ptr<StatusItem> newItem = std::make_unique<StatusItem>(initData);
		GetOwner()->AddNewActor(std::move(newItem));
	}
	else if (rv < 0.75f)
	{
		// AmmoItem
		AmmoItem::InitData initData;
		initData.spawnPos = GetPosition();

		float rvStat = Util::Randomf(0.0f, 1.0f);
		if (rvStat < 0.2f)
		{
			initData.type = AmmoItem::WeaponType::Pistol;
			initData.amount = 18;
		}
		else if (rvStat < 0.4f)
		{
			initData.type = AmmoItem::WeaponType::Uzi;
			initData.amount = 35;
		}
		else if (rvStat < 0.6f)
		{
			initData.type = AmmoItem::WeaponType::Shotgun;
			initData.amount = 8;
		}
		else if (rvStat < 0.8f)
		{
			initData.type = AmmoItem::WeaponType::Barrel;
			initData.amount = 3;
		}
		else
		{
			initData.type = AmmoItem::WeaponType::Railgun;
			initData.amount = 6;
		}

		std::unique_ptr<AmmoItem> newItem = std::make_unique<AmmoItem>(initData);
		GetOwner()->AddNewActor(std::move(newItem));
	}
}
