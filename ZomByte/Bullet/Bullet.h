#pragma once

#include "Actor/Actor.h"

#include "Util/Timer.h"

using namespace JD;

class Bullet : public Actor
{
	RTTI_DECLARATIONS(Bullet, Actor)

	struct InitData
	{
		int dirIdx = 0;
		float lifeTime = 0.0f;
		float moveSpeed = 0.0f;
		Vector2<float> firePos;
		Vector2<float> fireDir;
	};

	static const char* bulletImage[8];

public:
	Bullet(const InitData& initData);

private:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

private:
	void UpdateMovement(float deltaTime);

private:
	Timer timer;
	Vector2<float> direction;
	float moveSpeed = 0.0f;
};
