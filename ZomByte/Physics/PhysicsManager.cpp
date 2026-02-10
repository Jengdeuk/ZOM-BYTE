#include "PhysicsManager.h"

#include "Actor/Character/Player.h"
#include "Actor/Character/Zombie.h"
#include "Actor/Projectile/Bullet.h"
#include "Actor/Projectile/PlacedBarrel.h"
#include "Actor/Effect/Railslug.h"
#include "Actor/Effect/ExplosionEffect.h"
#include "Actor/Item/Item.h"

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
	ProcessCollisionBullet(actors, deltaTime);
	ProcessCollisionRailslug(actors, deltaTime);
	ProcessCollisionExplosionEffect(actors, deltaTime);
	ProcessCollisionItem(actors, deltaTime);
}

void PhysicsManager::ProcessCollisionBullet(const Actors& actors, float deltaTime)
{
	std::vector<Bullet*> bullets;
	std::vector<Actor*> others;

	for (auto& actor : actors)
	{
		if (actor->IsTypeOf<Bullet>())
		{
			bullets.emplace_back(actor.get()->As<Bullet>());
		}
		else if (actor->IsTypeOf<Zombie>() || actor->IsTypeOf<PlacedBarrel>())
		{
			others.emplace_back(actor.get());
		}
	}

	const float inf = 12345678.9f;
	const float dstRadius = 1.0f;
	for (auto& bullet : bullets)
	{
		float minT = inf;
		Actor* target = nullptr;

		for (auto& other : others)
		{
			Character* character = nullptr;
			if (other->IsTypeOf<Character>())
			{
				character = other->As<Character>();
			}

			if (character && character->IsDead())
			{
				continue;
			}

			float t = inf - 5.0f;
			if (!CheckBulletHit(t, bullet->GetLastPos(), bullet->GetPosition(), other->GetPosition(), dstRadius))
			{
				continue;
			}

			if (t < minT)
			{
				minT = t;
				target = other;
			}
		}

		if (!target)
		{
			continue;
		}

		bullet->Destroy();

		if (target->IsTypeOf<Character>())
		{
			Character* character = target->As<Character>();
			const Vec2f& knockBackDir = bullet->GetFireDir();
			const float force = 15.0f * static_cast<float>(bullet->GetWeaponInitDamage());
			character->AccumulateForce(knockBackDir * force);
			character->OnDamaged(bullet->GetDamage());
		}
		else if (target->IsTypeOf<PlacedBarrel>())
		{
			PlacedBarrel* barrel = target->As<PlacedBarrel>();
			barrel->Explosion();
		}
	}
}

void PhysicsManager::ProcessCollisionRailslug(const Actors& actors, float deltaTime)
{
	std::vector<Railslug*> effects;
	std::vector<Actor*> others;

	for (auto& actor : actors)
	{
		if (actor->IsTypeOf<Railslug>())
		{
			effects.emplace_back(actor.get()->As<Railslug>());
		}
		else if (actor->IsTypeOf<Zombie>() || actor->IsTypeOf<PlacedBarrel>())
		{
			others.emplace_back(actor.get());
		}
	}

	float p = 0.0f;
	for (auto& effect : effects)
	{
		for (auto& other : others)
		{
			const Vec2f& ePos = effect->GetPosition();
			const Vec2f& oPos = other->GetPosition();
			if (CheckPenetration(p, ePos, oPos, 1.0f))
			{
				if (other->IsTypeOf<Character>())
				{
					Character* character = other->As<Character>();
					const Vec2f& knockBackDir = (oPos - ePos).Normalized();
					const float force = 1.5f * static_cast<float>(effect->GetWeaponInitDamage());
					character->AccumulateForce(knockBackDir * force);
					character->OnDamaged(effect->GetDamage());
				}
				else if (other->IsTypeOf<PlacedBarrel>())
				{
					PlacedBarrel* barrel = other->As<PlacedBarrel>();
					barrel->Explosion();
				}
			}
		}
	}
}

void PhysicsManager::ProcessCollisionExplosionEffect(const Actors& actors, float deltaTime)
{
	std::vector<ExplosionEffect*> effects;
	std::vector<Actor*> others;

	for (auto& actor : actors)
	{
		if (actor->IsTypeOf<ExplosionEffect>())
		{
			effects.emplace_back(actor.get()->As<ExplosionEffect>());
		}
		else if (actor->IsTypeOf<Character>() || actor->IsTypeOf<PlacedBarrel>())
		{
			others.emplace_back(actor.get());
		}
	}

	float p = 0.0f;
	for (auto& effect : effects)
	{
		for (auto& other : others)
		{
			const Vec2f& ePos = effect->GetPosition();
			const Vec2f& oPos = other->GetPosition();
			if (CheckPenetration(p, ePos, oPos, 1.0f))
			{
				if (other->IsTypeOf<Character>())
				{
					Character* character = other->As<Character>();
					const Vec2f& knockBackDir = (oPos - ePos).Normalized();
					const float force = 5.0f * static_cast<float>(effect->GetWeaponInitDamage());
					character->AccumulateForce(knockBackDir * force);
					character->OnDamaged(effect->GetDamage());
				}
				else if (other->IsTypeOf<PlacedBarrel>())
				{
					PlacedBarrel* barrel = other->As<PlacedBarrel>();
					barrel->Explosion();
				}
			}
		}
	}
}

void PhysicsManager::ProcessCollisionItem(const Actors& actors, float deltaTime)
{
	std::vector<Item*> items;
	Player* player = nullptr;

	for (auto& actor : actors)
	{
		if (actor->IsTypeOf<Item>())
		{
			items.emplace_back(actor.get()->As<Item>());
		}
		else if (actor->IsTypeOf<Player>())
		{
			player = actor.get()->As<Player>();
		}
	}

	if (!player)
	{
		return;
	}

	float p = 0.0f;
	for (auto& item : items)
	{
		if (CheckPenetration(p, item->GetPosition(), player->GetPosition(), 0.5f))
		{
			item->ApplyEffect(player);
		}
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
				const bool isAMovable = a->IsTypeOf<Character>() || a->IsTypeOf<Item>();
				const bool isBMovable = b->IsTypeOf<Character>() || b->IsTypeOf<Item>();

				const Vec2f n = bPos - aPos;
				if (isAMovable && isBMovable)
				{
					a->SetPosition(aPos + n * p * -0.5f);
					b->SetPosition(bPos + n * p * 0.5f);
				}
				else if (isAMovable)
				{
					a->SetPosition(aPos + n * p * -1.0f);
				}
				else if (isBMovable)
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
