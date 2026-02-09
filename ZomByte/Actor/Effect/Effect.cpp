#include "Effect.h"

Effect::Effect(const Actor::InitData& initData)
	: Super(initData)
{
}

void Effect::Init(const EffectFrame* initSequence, const int size)
{
	sequence = initSequence;
	effectSequenceCount = size;

	timer.SetTargetTime(sequence[0].playTime);
	SetImage((sequence[0].image).get());
	SetColor(sequence[0].color);
}

void Effect::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	timer.Tick(deltaTime);
	if (!timer.IsTimeOut())
	{
		return;
	}

	if (currentSequenceIndex == effectSequenceCount - 1)
	{
		Destroy();
		return;
	}

	++currentSequenceIndex;

	timer.Reset();
	timer.SetTargetTime(sequence[currentSequenceIndex].playTime);
	SetImage((sequence[currentSequenceIndex].image).get());
	SetColor(sequence[currentSequenceIndex].color);
}
