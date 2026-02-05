#include "GameLevel.h"

#include "Engine/Engine.h"

#include "Character/Player.h"

#include <memory>

using namespace JD;

GameLevel::GameLevel(const Vector2<int>& mapSize)
	: mapSize(mapSize)
{
	Actor::InitData initData;
	initData.image = "P";
	initData.color = Color::DarkYellow;
	initData.position = Vector2<int>(mapSize.x >> 1, mapSize.y >> 1);
	initData.sortingOrder = 10;

	Character::Status status;
	status.healthPoint = 5;
	status.attackRate = 1;
	status.moveSpeed = 6;

	AddNewActor(std::make_unique<Player>(initData, status));
}
