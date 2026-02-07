#pragma once

#include "Effect.h"

using namespace JD;

class BloodEffect : public Effect
{
	RTTI_DECLARATIONS(BloodEffect, Effect)

public:
	BloodEffect(const Actor::InitData& initData);

private:
	virtual void Tick(float deltaTime) override;
};
