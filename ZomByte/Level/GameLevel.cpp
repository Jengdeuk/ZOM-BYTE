#include "GameLevel.h"

#include "Engine/Engine.h"
#include "Render/Renderer.h"
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

	std::unique_ptr<Player> newPlayer = std::make_unique<Player>(initData, status);
	player = newPlayer.get();
	AddNewActor(std::move(newPlayer));
}

void GameLevel::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	survivalTime += deltaTime;
	lastDeltaTime = deltaTime;
}

void GameLevel::Draw()
{
	Super::Draw();

	DrawHUD();
}

void GameLevel::DrawHUD()
{
	const int hp = (player->As<Character>())->GetHealthPoint();
	for (int i = 0; i < hp; ++i)
	{
		buffer_hp[i] = '*';
	}
	Renderer::Instance().Submit(buffer_hp, Vector2<int>(mapSize.x + 2, 2), Color::Red);

	sprintf_s(buffer_stime, "%d:%d", static_cast<int>(survivalTime / 60), static_cast<int>(survivalTime) % 60);
	Renderer::Instance().Submit(buffer_stime, Vector2<int>(mapSize.x + 2, 0), Color::Gray);

	sprintf_s(buffer_fps, "FPS:%d", static_cast<int>(1.0f / lastDeltaTime));
	Renderer::Instance().Submit(buffer_fps, Vector2<int>(Engine::Instance().GetScreenSize().x - 7, 0), Color::DarkGray);
}
