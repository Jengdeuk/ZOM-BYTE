#include "ExplosionEffect.h"

#include "Util/Util.h"

#include "Level/GameLevel.h"
#include "Actor/Character/Player.h"
#include "Actor/Item/StatusItem.h"
#include "Actor/Item/AmmoItem.h"

static const Effect::EffectFrame effectSequence[] =
{
	{"@", 0.08f, Color::Magenta},
	{"@", 0.08f, Color::White},
	{"@", 0.08f, Color::Magenta},
	{"@", 0.08f, Color::Gray},
	{"@", 0.08f, Color::DarkMagenta},
	{"@", 0.08f, Color::DarkGray}
};

ExplosionEffect::ExplosionEffect(const Actor::InitData& initData, const int damage, const int weaponDamage)
	: Super(initData),
	damage(damage),
	weaponDamage(weaponDamage)
{
	Effect::Init(effectSequence, sizeof(effectSequence) / sizeof(effectSequence[0]));
}

void ExplosionEffect::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}
