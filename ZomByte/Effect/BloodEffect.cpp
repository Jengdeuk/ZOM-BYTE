#include "BloodEffect.h"

static const Effect::EffectFrame effectSequence[] =
{
	{"#", 0.75f, Color::DarkRed},
	{"#", 0.75f, Color::DarkGray}
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

	}
}
