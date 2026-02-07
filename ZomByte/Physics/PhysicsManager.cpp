#include "PhysicsManager.h"

#include "Bullet/Bullet.h"
#include "Character/Player.h"
#include "Character/Zombie.h"

PhysicsManager& PhysicsManager::Instance()
{
	static PhysicsManager instance;
	return instance;
}

void PhysicsManager::PhysicsUpdate(const Actors& actors, float deltaTime)
{
	ProcessCollsionBulletToZombie(actors, deltaTime);

	//const int size = actors.size();
	//for (int i = 0; i < size - 1; ++i)
	//{
	//	Actor* lhs = actors[i].get();
	//	const Actor::CollisionFilter& lhsFilter = lhs->GetCollisionFilter();
	//	for (int j = i + 1; j < size; ++j)
	//	{
	//		Actor* rhs = actors[j].get();
	//		const Actor::CollisionFilter& rhsFilter = rhs->GetCollisionFilter();
	//
	//		if ((lhsFilter.mask & rhsFilter.layer) && (rhsFilter.mask & lhsFilter.layer))
	//		{
	//			// todo: 양방향 효과 적용
	//		}
	//		else if (lhsFilter.mask & rhsFilter.layer) // src: lhs
	//		{
	//			SelectCollisionFunction(lhs, rhs);
	//		}
	//		else if (rhsFilter.mask & lhsFilter.layer) // src: rhs
	//		{
	//			SelectCollisionFunction(rhs, lhs);
	//		}
	//	}
	//}
}

void PhysicsManager::SelectCollisionFunction(Actor* src, Actor* dst)
{
	if (src->IsTypeOf<Player>())
	{

	}
	else if (src->IsTypeOf<Zombie>())
	{

	}
	else if (src->IsTypeOf<Bullet>())
	{
		if (dst->IsTypeOf<Zombie>())
		{
			//ProcessCollsionBulletToZombie(src, dst);
		}
	}
}

static float Dot(const Vector2<float>& a, const Vector2<float>& b)
{
	return a.x * b.x + a.y * b.y;
}

static float LengthSq(const Vector2<float>& v)
{
	return Dot(v, v);
}

static float Clamp(float t)
{
	if (t < 0.f) return 0.f;
	if (t > 1.f) return 1.f;
	return t;
}

void PhysicsManager::ProcessCollsionBulletToZombie(const Actors& actors, float deltaTime)
{
	std::vector<Bullet*> bullets;
	std::vector<Zombie*> zombies;

	for (auto& actor : actors)
	{
		if (actor->IsTypeOf<Bullet>())
		{
			bullets.emplace_back(actor.get()->As<Bullet>());
		}
		else if (actor->IsTypeOf<Zombie>())
		{
			zombies.emplace_back(actor.get()->As<Zombie>());
		}
	}

	const float inf = 12345678.9f;
	const float dstRadius = 0.5f;
	for (auto& bullet : bullets)
	{
		float minT = inf;
		Zombie* target = nullptr;

		for (auto& zombie : zombies)
		{
			if (zombie->IsDead())
			{
				continue;
			}

			float t = inf - 5.0f;
			if (!CheckBulletHit(t, bullet->GetLastPos(), bullet->GetPosition(), zombie->GetPosition(), dstRadius))
			{
				continue;
			}

			if (t < minT)
			{
				minT = t;
				target = zombie;
			}
		}

		if (!target)
		{
			continue;
		}

		bullet->Destroy();

		const Vec2f& knockBackDir = bullet->GetFireDir();
		const int damage = bullet->GetDamage();
		const float force = 15.0f * static_cast<float>(damage);
		target->AccumulateForce(knockBackDir * force);
		target->OnDamaged(damage);
	}
}

bool PhysicsManager::CheckBulletHit(float& outT, const Vec2f& prvPos, const Vec2f& curPos, const Vec2f& dstPos, const float dstRadius)
{
	Vec2f dv = curPos - prvPos;
	float lenSq = LengthSq(dv);
	if (lenSq < 0.000001f)
	{
		return LengthSq(prvPos - dstPos) <= dstRadius * dstRadius;
	}

	// 선분 위에서 적 중심까지 가장 가까운 지점 찾기
	float t = Clamp(Dot(dstPos - prvPos, dv) / lenSq);

	Vec2f closestPoint = prvPos + dv * t;

	// 그 지점이 원 내부인지 검사
	return LengthSq(closestPoint - dstPos) <= dstRadius * dstRadius;
}
