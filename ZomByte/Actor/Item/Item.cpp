#include "Item.h"

#include "Physics/Collision.h"

Item::Item(Actor::InitData initData)
	: Super(initData)
{
	SetCollisionFilter(CollisionFilter{ ITEM, ZOMBIE | ITEM });
	timer.SetTargetTime(7.0f);
	timer.Reset();
}

void Item::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	timer.Tick(deltaTime);
	if (timer.IsTimeOut())
	{
		Destroy();
	}
}
