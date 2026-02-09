#include "PhysicsManager.h"

#include "Actor/Bullet/Bullet.h"
#include "Actor/Character/Player.h"
#include "Actor/Character/Zombie.h"

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

PhysicsManager& PhysicsManager::Instance()
{
	static PhysicsManager instance;
	return instance;
}

void PhysicsManager::PhysicsUpdate(const Actors& actors, float deltaTime)
{
	ProcessCollsionBullet(actors, deltaTime);
}

void PhysicsManager::ProcessCollsionBullet(const Actors& actors, float deltaTime)
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

void PhysicsManager::ResolvePenetration(const Actors& actors, float deltaTime)
{
	const int size = static_cast<int>(actors.size());
	for (int i = 0; i < size - 1; ++i)
	{
		Actor* a = actors[i].get();
		const Actor::CollisionFilter& aFilter = a->GetCollisionFilter();

		if (a->IsTypeOf<Bullet>())
		{
			continue;
		}

		for (int j = i + 1; j < size; ++j)
		{
			Actor* b = actors[j].get();
			const Actor::CollisionFilter& bFilter = b->GetCollisionFilter();

			if (b->IsTypeOf<Bullet>())
			{
				continue;
			}

			if (!(aFilter.mask & bFilter.layer) || !(bFilter.mask & aFilter.layer))
			{
				continue;
			}

			// 겹친만큼 서로 밀어내기
			float p = 0.0f;
			const Vec2f& aPos = a->GetPosition();
			const Vec2f& bPos = b->GetPosition();
			if (CheckPenetration(p, aPos, bPos, 0.5f))
			{
				const bool isACharacter = a->IsTypeOf<Character>();
				const bool isBCharacter = b->IsTypeOf<Character>();

				const Vec2f n = bPos - aPos;
				if (isACharacter && isBCharacter)
				{
					a->SetPosition(aPos + n * p * -0.5f);
					b->SetPosition(bPos + n * p * 0.5f);
				}
				else if (isACharacter)
				{
					a->SetPosition(aPos + n * p * -1.0f);
				}
				else if (isBCharacter)
				{
					b->SetPosition(bPos + n * p);
				}
			}
		}
	}
}

bool PhysicsManager::CheckBulletHit(float& outT, const Vec2f& prvPos, const Vec2f& curPos, const Vec2f& dstPos, const float dstRadius)
{
	const Vec2f dv = curPos - prvPos;
	const float lenSq = LengthSq(dv);
	if (lenSq < 0.000001f)
	{
		return LengthSq(prvPos - dstPos) <= dstRadius * dstRadius;
	}

	// 선분에 투영
	outT = Clamp(Dot(dstPos - prvPos, dv) / lenSq);

	// 선분 위에서 적 중심까지 가장 가까운 지점 찾기
	Vec2f closestPoint = prvPos + dv * outT;

	// 그 지점이 원 내부인지 검사
	return LengthSq(closestPoint - dstPos) <= dstRadius * dstRadius;
}

bool PhysicsManager::CheckPenetration(float& outP, const Vec2f& aPos, const Vec2f& bPos, const float colRadius)
{
	const float lSq = LengthSq(aPos - bPos);
	const float rSq = 4 * colRadius * colRadius;

	outP = sqrt(rSq) - sqrt(lSq);

	return lSq <= rSq;
}
