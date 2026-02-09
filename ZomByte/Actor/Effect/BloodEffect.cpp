#include "BloodEffect.h"

#include "Util/Util.h"

#include "Level/GameLevel.h"
#include "Actor/Character/Player.h"
#include "Actor/Item/StatusItem.h"

static const Effect::EffectFrame effectSequence[] =
{
	{"#", 1.0f, Color::DarkRed},
	{"#", 0.5f, Color::DarkGray}
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
	if (rv < 0.5f)
	{
		// StatusItem
		StatusItem::InitData initData;
		initData.spawnPos = GetPosition();

		float rvStat = Util::Randomf(0.0f, 1.0f);
		if (rvStat < 0.5f)
		{
			// HP
			initData.status = StatusItem::Status::HealthPoint;
			initData.amount = 1;
		}
		else if (rvStat < 0.75f)
		{
			// AR
			initData.status = StatusItem::Status::AttackRate;
			initData.amount = 1;
		}
		else
		{
			// MS
			initData.status = StatusItem::Status::MoveSpeed;
			initData.amount = 1;
		}

		std::unique_ptr<StatusItem> newItem = std::make_unique<StatusItem>(initData);
		GetOwner()->AddNewActor(std::move(newItem));
	}
	else
	{
		// WeaponItem

	}
}
