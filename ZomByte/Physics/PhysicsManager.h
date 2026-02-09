#pragma once

#include "Actor/Actor.h"

#include <vector>

using namespace JD;

class PhysicsManager
{
private:
	PhysicsManager() = default;

	PhysicsManager(const PhysicsManager&) = delete;
	PhysicsManager& operator=(const PhysicsManager&) = delete;

public:
	static PhysicsManager& Instance();

public:
	using Actors = std::vector<std::unique_ptr<Actor>>;
	void PhysicsUpdate(const Actors& actors, float deltaTime);

private:
	void ProcessCollisionBullet(const Actors& actors, float deltaTime);
	void ProcessCollisionRailslug(const Actors& actors, float deltaTime);
	void ProcessCollisionExplosionEffect(const Actors& actors, float deltaTime);
	void ProcessCollisionItem(const Actors& actors, float deltaTime);
	
public:
	void ResolvePenetration(const Actors& actors, float deltaTime);

private:
	using Vec2f = Vector2<float>;
	bool CheckBulletHit(float& outT, const Vec2f& prvPos, const Vec2f& curPos, const Vec2f& dstPos, const float dstRadius);
	bool CheckPenetration(float& outP, const Vec2f& aPos, const Vec2f& bPos, const float colRadius);
};
