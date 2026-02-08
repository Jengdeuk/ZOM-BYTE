#pragma once

#include "Level/Level.h"

#include "Math/Vector2.h"

using namespace JD;

class Player;

class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel(const Vector2<int>& mapSize);

public:
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

public:
	void PhysicsUpdate(float deltaTime);
	void TransformUpdate(float deltaTime);

public:
	void OnKilled();

private:
	void LoadGround(const char* filename);

public:
	inline const Vector2<int>& GetMapSize() const { return mapSize; }
	inline Player* GetPlayer() const { return player; };
	inline void SetCurrentWeaponIndex(int index) { currentWeaponIndex = index; }

private:
	void DrawHUD();

private:
	Vector2<int> mapSize;
	Player* player = nullptr;

private:
	int killed = 0;
	float survivalTime = 0.0f;
	int currentWeaponIndex = 0;

private:
	float lastDeltaTime = 0.0f;

private:
	std::unique_ptr<char[]> backgroundImg;

private:
	char buffer_hp[256] = {};
	char buffer_killed[256] = {};
	char buffer_stime[256] = {};
	char buffer_fps[256] = {};
};
