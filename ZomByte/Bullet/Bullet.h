#pragma once

#include "Actor/Actor.h"

#include "Util/Timer.h"

using namespace JD;

class Bullet : public Actor
{
	RTTI_DECLARATIONS(Bullet, Actor)

	struct InitData
	{
		int damage = 0;
		int dirIdx = 0;
		float lifeTime = 0.0f;
		float moveSpeed = 0.0f;
		float drag = 0.0f;
		Vector2<float> fireDir;
	};

	static const char* bulletImage[8];

public:
	Bullet(const Actor::InitData& actorInitData, const InitData& initData);

private:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

private:
	void UpdateMovement(float deltaTime);

private:
	int damage = 0;
	Timer timer;
	Vector2<float> direction;
	float moveSpeed = 0.0f;
	float drag = 0.0f;

private:
	Vector2<float> lastPosition;
};
