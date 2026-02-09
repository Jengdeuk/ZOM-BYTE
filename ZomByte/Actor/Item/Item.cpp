#include "Item.h"

#include "Physics/Collision.h"

Item::Item(Actor::InitData initData)
	: Super(initData)
{
	SetCollisionFilter(CollisionFilter{ ITEM, ZOMBIE | ITEM });
}
